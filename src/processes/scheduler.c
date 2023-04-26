/**
 * Copyright (C) 2023 pitulst
 *
 * This file is part of LuaOS.
 *
 * LuaOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LuaOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "luck/processes/scheduler.h"

#include <lua.h>
#include "string.h"

#include "luck/arch/x86_64/cpu.h"
#include "luck/io/log.h"
#include "luck/memory/manager.h"
#include "luck/bootloader/limine.h"


#include "lj-libc/limits.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void *ljsup_alloc(void *ud, void *ptr, size_t osize, size_t nsize);

#define _lua_openmodule(mname, module) ({ \
    lua_pushcfunction(L, luaopen_##module); \
    lua_pushstring(L, mname); \
    lua_call(L, 1, 0); \
})
#define lua_openmodule(module) _lua_openmodule(#module, module)

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

    debug("Killing thread {}", t->name);
    t->kill = true;
    while (true) asm("HLT");
}

static Lock sched_lock = false;
static Thread *nullable ready = nullptr;
static Thread *nullable ready_tail = nullptr;
static Thread *nullable idle = nullptr;

Thread *spawn_thread(void *addr, size_t size, const char *name)
{
    Thread *t = kalloc(sizeof(Thread));

    lua_State *L = t->lua = lua_newstate(ljsup_alloc, nullptr);
    if (L == nullptr)
        return nullptr;

    _lua_openmodule("", base);
    lua_openmodule(table);
    lua_openmodule(string);
    lua_openmodule(math);
    lua_openmodule(debug);
    lua_openmodule(bit);
    luaopen_kernel(L);

    size_t name_len = string_length(name);
    if (string_length(name) < 64) {
        string_copy(64, t->name, name_len, name);
    } else {
        memory_copy(t->name, name, 63);
        t->name[63] = 0;
    }
    int v = luaL_loadbuffer(L, addr, size, t->name);
    if (v != 0)
        panic("Could not spawn thread! Reason: {}", lua_tostring(L, -1));

    t->stack_base = kalloc(Thread_STACKSIZE);
    if (!t->stack_base) panic("failed to allocate stack");
    t->cpu_context.rsp = (uint64_t)(t->stack_base + Thread_STACKSIZE);
    t->cpu_context.rip = (uint64_t)(thread_entry);
    t->cpu_context.rdi = (uint64_t)(t);
    t->cpu_context.rflags = 0x202; // all the flags that we need
    t->cpu_context.cs = 0x28;
    t->cpu_context.ss = 0x30;
    t->ready = true;

    acquire_lock(&sched_lock);
    t->next_task = ready;
    if (ready) {
        ready->previous_task = t;
    } else {
        // TODO: in debug (or some kind of "safe") mode only
        if (ready_tail) panic("i'm an expert at linked lists");
        ready_tail = t;
    }
    ready = t;
    release_lock(&sched_lock);

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
void scheduler_init(void)
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

    acquire_lock(&t->lock);
    lua_close(t->lua);
    t->cpu_context.rip = 0xdeadbeefdeadbeef;
    kfree(t->stack_base, 16384);
    kfree(t, sizeof(Thread));
    release_lock(&t->lock);
    asm("MOVQ $0, (%%RDI)\n1: INT3\njmp 1b" :: "D"(&threadsweeper_lock));
}

void reschedule(CPUContext *nonnull ctx)
{
    if (atomic_load(&sched_lock)) return;
    acquire_lock(&sched_lock);
    uint64_t lapic = *lapic_id >> 24;
    if (ctx->interrupt_number == 3) {
        if (!was_threadsweeping[lapic]) {
            panic("invalid int3!");
        }
    }
    if (threads[lapic]) {
        Thread *told = threads[lapic];
        if (atomic_load(&told->lock)) return;
        acquire_lock(&told->lock);
        told->cpu_context = *ctx;
        if (told->ready) {
            if (ready_tail) {
                ready_tail->next_task = told;
                told->previous_task = ready_tail;
            } else {
                ready = ready_tail = told;
            }
        } else {
            if (idle) idle->previous_task = told;
            told->next_task = idle;
            idle = told;
        }
        release_lock(&threads[lapic]->lock);
    } else {
        if (!was_threadsweeping[lapic]) idle_tasks[lapic] = *ctx;
    }
    if (ready) {
        auto tnew = (Thread *nonnull)ready;

        if (atomic_load(&tnew->lock)) goto idle;
        acquire_lock(&tnew->lock);
        if (tnew->next_task) {
            tnew->next_task->previous_task = nullptr;
            ready = tnew->next_task;
            tnew->next_task = nullptr;
        } else {
            ready_tail = ready = nullptr;
        }
        threads[lapic] = tnew;
        *ctx = tnew->cpu_context;
        if (!tnew->ready) panic("how is a non-ready task on the ready list?");
        if (tnew->kill) {
            acquire_lock(&threadsweeper_lock);
            ctx->rip = (uint64_t)(threadsweeper);
            ctx->rsp = (uint64_t)(threadsweeper_stack + 16384);
            ctx->rdi = (uint64_t)(tnew);
            ctx->rflags = 0x2;
            was_threadsweeping[lapic] = true;
            threads[lapic] = nullptr;
        } else {
            ctx->rflags = 0x202;
        }
        release_lock(&tnew->lock);
    } else {
    idle:
        *ctx = idle_tasks[lapic];
        threads[lapic] = nullptr;
        ctx->rflags = 0x202;
    }
    release_lock(&sched_lock);
}

void wait_for_thread(Thread *thread)
{
    acquire_lock(&thread->lock);

    while (!thread->kill) {
        release_lock(&thread->lock);
        reschedule(&thread->cpu_context); // This will cause the current thread to yield
        release_lock(&thread->lock);
    }

    release_lock(&thread->lock);
}

void wake_futex(Futex *mtx)
{
    acquire_lock(&mtx->lock);

    if (mtx->head) {
        Thread *to_wake = mtx->head;
        mtx->head = assert_nonnull(to_wake->next_mutex)({
            goto done;
        });

        acquire_lock(&to_wake->lock);\
        to_wake->next_mutex = nullptr;
        to_wake->ready = true;
        release_lock(&to_wake->lock);
    }

    done:
    release_lock(&mtx->lock);
}

void wake_all_futexes(Futex *mtx)
{
    acquire_lock(&mtx->lock);

    while (mtx->head) {
        Thread *to_wake = mtx->head;
        mtx->head = assert_nonnull(to_wake->next_mutex)({
            goto done;
        });

        acquire_lock(&to_wake->lock);\
        to_wake->next_mutex = NULL;
        to_wake->ready = true;
        release_lock(&to_wake->lock);
    }

    done:
    acquire_lock(&mtx->lock);
}

// function scheduler.spawn(modulename: string, ...: string): Thread
static int libscheduler_spawn(lua_State *nonnull L)
{


    return 1;
}

static const luaL_Reg libscheduler[] = {
    { "spawn", libscheduler_spawn },
    { nullptr, nullptr }
};

int luaopen_scheduler(lua_State *nonnull L)
{

    return 1;
}
