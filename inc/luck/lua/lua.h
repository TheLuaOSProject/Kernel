#pragma once

#include <stdatomic.h>
#include <stddef.h>

#include "luck/arch/x86_64/cpu.h"
#include <LuaJIT/src/lua.h>

typedef struct Thread {
	char name[64];
	CPUContext ctx;
	void* stack_base;
	struct Thread* sched_next;
	struct Thread* sched_prev;
	lua_State *L;
	bool ready, kill;
	atomic_bool lock;
} Thread;

Thread *init_thread(void* addr, size_t size, const char* name);
void reschedule(CPUContext* ctx);
void sched_init(void);
