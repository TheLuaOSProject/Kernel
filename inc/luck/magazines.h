/**
 * Copyright (C) 2023 pitust
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

#pragma once

#include <common.h>
#include <stdatomic.h>

typedef union {
	struct {
		atomic_bool locked;
		qword* current;
		qword* previous;
	};
	char padding[64]; // force cache line size to avoid false sharing
} mag_percpu_t;
typedef struct {
	atomic_bool locked;

	qword num_ready_mags;
	qword* ready_mags[16];

	qword num_free_mags;
	qword* free_mags[16];

	qword(*get)(void* ctx);
	void (*put)(void* ctx, qword item);
	void* ctx;
	mag_percpu_t* mag_percpu;
} magazine_t;

#define MAG_MUSTGET 1

magazine_t* mag_new(qword(*get)(void* ctx), void (*put)(void* ctx, qword item), void* ctx);
void mag_destroy(magazine_t* mag);
void mag_put(magazine_t* mag, qword item);
bool mag_xget(magazine_t* mag, qword* out, uint64_t flags);
qword mag_get(magazine_t* mag);
void mag_100ms_adjust(void);
void mag_init(void);
