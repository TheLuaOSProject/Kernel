/**
 * Copyright (C) 2023 Amrit Bhogal
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

#include <LuaJIT/src/lua.h>

#include "common.h"
#include "luck/arch/x86_64/cpu.h"

NONNULL_BEGIN

enum {
    Thread_STACKSIZE = 0x4000,
};

struct Message {
    struct Message *nullable next, *nullable previous;
    size_t length;
    byte data[];
};

struct Channel {
    struct Message *read_head, *write_head;
    size_t byte_count, byte_max;
    size_t message_count, message_max;
};

typedef struct Futex {
    struct Thread *head;
    Lock lock;
} Futex;

typedef struct Thread {
    char name[64];
    CPUContext ctx;
    void *stack_base;
    struct Thread *nullable next_task, *nullable previous_task;
    lua_State *lua;
    bool ready, kill;
    Lock lock;

    struct Thread *nullable next_mutex;
} Thread;

int wait_for_thread(Thread *thread);
int wake_mutex(Futex *mtx);
int wake_all_mutexes(Futex *mutexes);

Thread *nullable spawn_thread(void *addr, size_t size, const char *vpi);
void reschedule(CPUContext *ctx);
void scheduler_init(void);

NONNULL_END
