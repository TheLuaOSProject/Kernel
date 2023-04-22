#include <LuaJIT/src/lua.h>
#include "string.h"

#include "luck/arch/x86_64/cpu.h"
#include "luck/io/log.h"
#include "luck/lua/lua.h"
#include "luck/memory/manager.h"

void *ljsup_alloc(void *ud, void *ptr, size_t osize, size_t nsize);
int luaL_loadbuffer(lua_State *L, const char *s, size_t len, const char *name);

#define _lua_openmodule(mname, module) ({ \
    lua_pushcfunction(L, luaopen_##module); \
    lua_pushstring(L, mname); \
    lua_call(L, 1, 0); \
})
#define lua_openmodule(module) _lua_openmodule(#module, module)

int luaopen_base(lua_State *L);
int luaopen_math(lua_State *L);
int luaopen_string(lua_State *L);
int luaopen_table(lua_State *L);
int luaopen_debug(lua_State *L);
int luaopen_bit(lua_State *L);
int luaopen_llc(lua_State *L);
int luaopen_kernel(lua_State *L);

static void thread_entry(Thread *nonnull t)
{
    lua_State *L = t->lua;

    if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
        lua_pop(L, lua_gettop(L));
    } else {
        error("lua error: {}", lua_tostring(L, lua_gettop(L)));
        lua_pop(L, lua_gettop(L));
    }
    t->kill = true;
    while (true) asm("HLT");
}

static void ttas_lock(atomic_bool *nonnull b) {
    bool scc = false;
    do {
        while (atomic_load_explicit(b, memory_order_relaxed)) { scc = true; asm("pause"); }
    } while (atomic_exchange(b, true));
}
static void ttas_unlock(atomic_bool *b) {
    atomic_store(b, false);
}
static atomic_bool sched_lock = false;
static Thread *nullable ready = nullptr;
static Thread *nullable ready_tail = nullptr;
static Thread *nullable idle = nullptr;

Thread *init_thread(void *addr, size_t size, const char *name)
{
    Thread *t = kalloc(sizeof(Thread));
    if (t == nullptr) return nullptr;

    int status;
    lua_State *L;

    L = t->lua = lua_newstate(ljsup_alloc, nullptr);
    if (L == nullptr)
        return nullptr;

    _lua_openmodule("", base);
    lua_openmodule(table);
    lua_openmodule(string);
    lua_openmodule(math);
    lua_openmodule(debug);
    lua_openmodule(bit);
    luaopen_llc(L);
    luaopen_kernel(L);

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

static Thread *nullable threads[256];
static CPUContext idle_tasks[256];
static bool was_threadsweeping[256];
void sched_init(void)
{
    lapic_id = virt(get_lapic_addr_dyn() & ~0xfff, dword);
}

static void idle_task(void)
{
    info("welcome to the luaOS idle task for whatever core i'm on. I'm just chillin' here...");
    while (true) asm("hlt");
}
static atomic_bool threadsweeper_lock;
static __attribute__((aligned(16))) uint8_t threadsweeper_stack[16384];

static void threadsweeper(Thread *nonnull t) {
    uint64_t lapic = *lapic_id >> 24;

    ttas_lock(&t->lock);
    lua_close(t->lua);
    t->ctx.rip = 0xdeadbeefdeadbeef;
    kfree(t->stack_base, 16384);
    kfree(t, sizeof(Thread));
    ttas_unlock(&t->lock);
    asm("MOVQ $0, (%%RDI)\n1: INT3\njmp 1b" :: "D"(&threadsweeper_lock));
}

void reschedule(CPUContext *nonnull ctx)
{
    if (atomic_load(&sched_lock)) return;
    ttas_lock(&sched_lock);
    uint64_t lapic = *lapic_id >> 24;
    if (ctx->interrupt_number == 3) {
        if (!was_threadsweeping[lapic]) {
            panic("invalid int3!");
        }
    }
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
        if (!was_threadsweeping[lapic]) idle_tasks[lapic] = *ctx;
    }
    if (ready) {
        Thread *nonnull tnew = assert_nonnull(ready)(({
            ready = ready->sched_next;
            if (ready != nullptr) ready->sched_prev = nullptr;
            else ready_tail = nullptr;
        }));

        if (atomic_load(&tnew->lock)) goto idle;
        ttas_lock(&tnew->lock);
        if (tnew->sched_next) {
            tnew->sched_next->sched_prev = nullptr;
            ready = tnew->sched_next;
            tnew->sched_next = nullptr;
        } else {
            ready_tail = ready = nullptr;
        }
        threads[lapic] = tnew;
        *ctx = tnew->ctx;
        if (!tnew->ready) panic("how is a non-ready task on the ready list?");
        if (tnew->kill) {
            ttas_lock(&threadsweeper_lock);
            ctx->rip = (uint64_t)(threadsweeper);
            ctx->rsp = (uint64_t)(threadsweeper_stack + 16384);
            ctx->rdi = (uint64_t)(tnew);
            ctx->rflags = 0x2;
            was_threadsweeping[lapic] = true;
            threads[lapic] = nullptr;
        } else {
            ctx->rflags = 0x202;
        }
        ttas_unlock(&tnew->lock);
    } else {
    idle:
        *ctx = idle_tasks[lapic];
        threads[lapic] = nullptr;
        ctx->rflags = 0x202;
    }
    ttas_unlock(&sched_lock);
}

