/**
 * Copyright (C) 2023 Amrit Bhogal, pitust
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

#include <common.h>
#include <stdatomic.h>

#include "luck/io/log.h"
#include "luck/magazines.h"
#include "luck/mm.h"
#include "memory.h"

#define mag_each_size 512
#define max_static_mag 2
#define max_ready_mags 32

static magazine_t static_mags[max_static_mag];
static atomic_llong num_static_mag = 0;
static mag_percpu_t mag_percpu[max_static_mag * 256];

static qword static_mag_alloc[mag_each_size * 32];
static qword static_mag_alloc_idx = 0;

static atomic_llong contended, total_attempts, mag_size_max = 128;

static volatile dword *lapic_id;

static attribute(naked) qword get_lapic_addr_dyn(void) {
	asm ("movl $0x1b, %ecx");
	asm ("rdmsr");
	asm ("shrq $32, %rdx");
	asm ("orq %rax, %rdx");
	asm ("retq");
}

void mag_init(void) {
	lapic_id = virt(get_lapic_addr_dyn() & ~0xfff, dword);
}

#define max_lapic_id 2 // TODO: change this to the actual value once we do smp 

magazine_t *mag_new(qword(*get)(void *ctx), void (*put)(void *ctx, qword item), void *ctx) {
	magazine_t *mag = nullptr;
	uint64_t mag_id = atomic_fetch_add(&num_static_mag, 1);
	if (mag_id < max_static_mag) {
		mag = &static_mags[mag_id];
		memory_set(mag, 0, sizeof(magazine_t));
		mag->mag_percpu = &mag_percpu[mag_id * 256];
		memory_set(mag->mag_percpu, 0, sizeof(mag_percpu_t) * 256);
		if (*lapic_id >= 256) panic("arch_get_max_cpu_id() >= 256; luaOS supports a maximum of 256 cores!");
	} else {
		mag = kalloc(sizeof(magazine_t));
		mag->mag_percpu = kalloc(sizeof(mag_percpu_t) * max_lapic_id);
	}
	mag->get = get;
	mag->put = put;
	mag->ctx = ctx;
	return mag;
}
static qword *alloc_mag(void) {
	if (static_mag_alloc_idx >= 32) panic("out of static magazine allocation space!");
	return &static_mag_alloc[static_mag_alloc_idx++ * mag_each_size + 1];
}
static void free_mag(qword *mag) {
	(void)mag;
	panic("TODO: free magazines (needs kmalloc)");
}
static void ttas_lock(atomic_bool *b) {
	bool scc = false;
	do {
		while (atomic_load_explicit(b, memory_order_relaxed)) { scc = true; asm("pause"); }
	} while (atomic_exchange(b, true));
	if (scc) atomic_fetch_add(&contended, 1);
	atomic_fetch_add(&total_attempts, 1);
}
static void ttas_unlock(atomic_bool *b) {
	atomic_store(b, false);
}

#define SWAP(a, b) do { __auto_type _tmp = (a); (a) = (b); (b) = _tmp; } while (0)
void mag_put(magazine_t *mag, qword item) {
	mag_percpu_t *mag_cpu = &mag->mag_percpu[*lapic_id >> 24];
	ttas_lock(&mag_cpu->locked);
free:
	if (mag_cpu->current && mag_cpu->current[-1] < mag_size_max) {
		// TODO: i really really really don't want this in the hot path for free
		if (__builtin_expect(!mag_cpu->current, 0)) mag_cpu->current = alloc_mag();
		mag_cpu->current[mag_cpu->current[-1]++] = item;
	} else if (mag_cpu->previous && mag_cpu->previous[-1] == 0) {
		SWAP(mag_cpu->previous, mag_cpu->current);
		goto free;
	} else if (atomic_load((atomic_ullong*)&mag->num_ready_mags) < max_ready_mags) {
		bool done = false;
		ttas_lock(&mag->locked);
		if (mag->num_ready_mags < max_ready_mags) {
			if (mag_cpu->current) mag->ready_mags[mag->num_ready_mags++] = mag_cpu->current;
			if (mag->num_free_mags) {
				mag_cpu->current = mag->free_mags[--mag->num_free_mags];
			} else {
				mag_cpu->current = alloc_mag();
			}
			done = true;
			ttas_unlock(&mag->locked);
		} else {
			ttas_unlock(&mag->locked);
			goto release;
		}
	} else {
release:;
		if (!mag_cpu->current) panic("this is prooobably dead code");
		uint64_t mag_cur_size = mag_cpu->current[-1];
		for (uint64_t i = 0;i < mag_cur_size;i++) {
			mag->put(mag->ctx, mag_cpu->current[i]);
			mag_cpu->current[i] = 0;
		}
		mag_cpu->current[-1] = 0;
	}
	ttas_unlock(&mag_cpu->locked);
}
bool mag_xget(magazine_t *mag, qword *out, uint64_t flags) {
	mag_percpu_t *mag_cpu = &mag->mag_percpu[*lapic_id >> 24];
	bool ok = false;
	ttas_lock(&mag_cpu->locked);
cur_mag_populated:
	if (mag_cpu->current && mag_cpu->current[-1]) {
		*out = mag_cpu->current[--mag_cpu->current[-1]];
		ok = true;
	} else if (mag_cpu->previous && mag_cpu->previous[-1]) {
		SWAP(mag_cpu->previous, mag_cpu->current);
		goto cur_mag_populated;
	} else if (atomic_load((atomic_ullong*)&mag->num_ready_mags)) {
		ttas_lock(&mag->locked);
		if (mag->num_ready_mags) {
			if (mag->num_free_mags < 16) {
				mag->free_mags[mag->num_free_mags++] = mag_cpu->current;
			} else {
				// todo: is the if needed?
				if (mag_cpu->current) {
					free_mag(mag_cpu->current);
				}
			}
			mag_cpu->current = mag->ready_mags[--mag->num_ready_mags];
			ttas_unlock(&mag->locked);
			// current magazine has been populated
			goto cur_mag_populated;
		} else {
			ttas_unlock(&mag->locked);
			// we need to get more resources
			goto allocate_new_obj;
		}
	} else {
allocate_new_obj:;
		if (flags & MAG_MUSTGET) {
			ttas_lock(&mag->locked);
			*out = mag->get(mag->ctx);
			ttas_unlock(&mag->locked);
			ok = true;
		}
	}
	ttas_unlock(&mag_cpu->locked);
	return ok;
}
qword mag_get(magazine_t *mag) {
	qword res = 0;
	mag_xget(mag, &res, MAG_MUSTGET);
	return res;
}
void mag_100ms_adjust(void) {
	qword contention = atomic_exchange(&contended, 0);
	qword tattempts = atomic_exchange(&total_attempts, 0);
	sqword delta = 0;
	if (contention * 30 < tattempts) delta = -1;
	if (contention * 10 >= tattempts) delta = 1;
	if (delta + mag_size_max >= mag_each_size - 1 && delta == 1) return;
	if (delta + mag_size_max < 16u && delta == -1) return;
	atomic_fetch_add(&mag_size_max, delta);
}
