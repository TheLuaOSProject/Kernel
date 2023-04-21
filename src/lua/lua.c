#include "luck/arch/x86_64/cpu.h"
#include "luck/io/log.h"
#include "../luajit/src/lua.h"
#include "luck/lua/lua.h"
#include "luck/memory/manager.h"
#include "string.h"

///
/// @category LuaJIT Support
/// LuaJIT allocator (defined in src/lib/libsupport.c)
///
void *ljsup_alloc(void *ud, void *ptr, size_t osize, size_t nsize);

///
/// @category LuaJIT Support
///
///
int luaL_loadbuffer(lua_State *L, const char *s, size_t len, const char *name);

void luaJIT_version_2_1_0_beta3(void);

void LJDBG(const char* msg)
{ success("lj: {}", msg); }

#define _lua_openmodule(mname, module) ({ \
    lua_pushcfunction(L, luaopen_##module); \
    lua_pushstring(L, mname); \
    lua_call(L, 1, 0);                   \
})
#define lua_openmodule(module) _lua_openmodule(#module, module)

LUALIB_API int luaopen_base(lua_State *L);
LUALIB_API int luaopen_math(lua_State *L);
LUALIB_API int luaopen_string(lua_State *L);
LUALIB_API int luaopen_table(lua_State *L);
LUALIB_API int luaopen_debug(lua_State *L);
LUALIB_API int luaopen_bit(lua_State *L);

static void thread_entry(Thread *t)
{
    lua_State *L = t->L;
    lua_call(L, 0, 0);
    panic("todo: exit thread");
}

static void ttas_lock(atomic_bool *b) {
    bool scc = false;
    do {
        while (atomic_load_explicit(b, memory_order_relaxed)) { scc = true; asm("pause"); }
    } while (atomic_exchange(b, true));
}
static void ttas_unlock(atomic_bool *b) {
    atomic_store(b, false);
}
static atomic_bool sched_lock = false;
static Thread* ready = nullptr;
static Thread* ready_tail = nullptr;
static Thread* idle = nullptr;

Thread *init_thread(void* addr, size_t size, const char* name)
{
    Thread *t = kalloc(sizeof(Thread));
    if (!t) return NULL;

    int status;
    lua_State *L;

    L = t->L = lua_newstate(ljsup_alloc, nullptr);
    if (!L) {
        panic("cant open lua");
    }
    
    _lua_openmodule("", base);
    lua_openmodule(table);
    lua_openmodule(string);
    lua_openmodule(math);
    lua_openmodule(debug);
    lua_openmodule(bit);
    
    if (string_length(name) < 64) {
        string_copy(t->name, name);
    } else {
        memory_copy(t->name, name, 63);
        t->name[63] = 0;
    }
    int v = luaL_loadbuffer(L, addr, size, t->name);
    if (v != 0) {
        panic("fail {}", lua_tostring(L, -1));
    }
    t->stack_base = kalloc(16384);
    if (!t->stack_base) panic("failed to allocate stack");
    t->ctx.rsp = (uint64_t)(t->stack_base + 16384);
    t->ctx.rip = (uint64_t)(thread_entry);
    t->ctx.rdi = (uint64_t)(t);
    t->ctx.rflags = 0x202; // all the flags that we need
    t->ctx.cs = 0x28;
    t->ctx.ss = 0x30;
    t->ready = true;

    ttas_lock(&sched_lock);
    t->sched_next = ready;
    if (ready) {
        ready->sched_prev = t;
    } else {
        // TODO: in debug (or some kind of "safe") mode only
        if (ready_tail) panic("i'm an expert at linked lists");
        ready_tail = t;
    }
    ready = t;
    ttas_unlock(&sched_lock);

    return t;
}

static volatile dword *lapic_id;

[[gnu::naked]]
static qword get_lapic_addr_dyn(void) {
    asm ("movl $0x1b, %ecx");
    asm ("rdmsr");
    asm ("shrq $32, %rdx");
    asm ("orq %rax, %rdx");
    asm ("retq");
}

static Thread *threads[256];
static CPUContext idle_tasks[256];
void sched_init(void)
{
    lapic_id = virt(get_lapic_addr_dyn() & ~0xfff, dword);
}

static void idle_task(void)
{
    info("welcome to the luaOS idle task for whatever core i'm on. I'm just chillin' here...");
    while (true) asm("hlt");
}

void reschedule(CPUContext* ctx)
{
    if (atomic_load(&sched_lock)) return;
    ttas_lock(&sched_lock);
    uint64_t lapic = *lapic_id >> 24;
    if (threads[lapic]) {
        Thread *told = threads[lapic];
        if (atomic_load(&told->lock)) return;
        ttas_lock(&told->lock);
        told->ctx = *ctx;
        if (told->ready) {
            if (ready_tail) {
                ready_tail->sched_next = told;
                told->sched_prev = ready_tail;
            } else {
                ready = ready_tail = told;
            }
        } else {
            if (idle) idle->sched_prev = told;
            told->sched_next = idle;
            idle = told;
        }
        ttas_unlock(&threads[lapic]->lock);
    } else {
        idle_tasks[lapic] = *ctx;
    }
    if (ready) {
        Thread *tnew = ready;
        if (atomic_load(&tnew->lock)) goto idle;
        ttas_lock(&tnew->lock);
        if (tnew->sched_next) {
            tnew->sched_next->sched_prev = nullptr;
            ready = tnew->sched_next;
            tnew->sched_next = nullptr;
        } else {
            ready_tail = nullptr;
        }
        threads[lapic] = tnew;
        *ctx = tnew->ctx;
        if (!tnew->ready) panic("how is a non-ready task on the ready list?");
        ttas_unlock(&tnew->lock);
    } else {
    idle:
        *ctx = idle_tasks[lapic];
        threads[lapic] = nullptr;
    }
    ttas_unlock(&sched_lock);
}

