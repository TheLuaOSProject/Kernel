#pragma once

#include <stdatomic.h>
#include <stddef.h>

#include "common.h"
#include "luck/arch/x86_64/cpu.h"
#include <LuaJIT/src/lua.h>

NONNULL_BEGIN

typedef struct Thread {
	char name[64];
	CPUContext ctx;
	void *stack_base;
	struct Thread *nullable sched_next;
	struct Thread *nullable sched_prev;
	lua_State *lua;
	bool ready, kill;
	atomic_bool lock;
} Thread;

Thread *nullable init_thread(void* addr, size_t size, const char* name);
void reschedule(CPUContext* ctx);
void sched_init(void);

NONNULL_END
