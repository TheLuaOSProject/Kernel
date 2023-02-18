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

#include "common.h"
#include "luck/io/log.h"
#include "luck/memory/manager.h"

static qword* get_pte(qword addr)
{
    addr <<= (64 - 48);
    qword cr3;
    asm volatile("MOVQ %%CR3, %0" : "=r"(cr3));
    qword* mod;
#define STEP(isfinal) \
    { \
        qword off = (addr >> (64 - 9)) & 0x1ff; \
        addr <<= 9; \
        qword* ptep = &virt(cr3, qword)[off]; \
        if (!isfinal && !(*ptep & 1)) { \
            *ptep = 7 | page_alloc(kPageTable); \
        } \
        if (isfinal) return ptep; \
        cr3 = *ptep & ~0xfff; \
    }

    STEP(0)
    STEP(0)
    STEP(0)
    STEP(1)
}

static void tlbinval(qword addr)
{
    asm volatile("invlpg (%0)" :: "r"(addr) : "memory");
}

void pmap_map(qword addr, qword phys)
{
    tlbinval(addr);
    *get_pte(addr) = 3 | phys | (1ULL << 63);
}

void pmap_map_rwx(qword addr, qword phys)
{
    tlbinval(addr);
    *get_pte(addr) = 3 | phys;
}

static void set_bits(qword addr, qword bits)
{
    qword *pte = get_pte(addr);
    qword pval = *pte;
    pval &= ~0xfff;
    pval &= ~(1ULL << 63);
    pval |= bits;
    *pte = pval;
    tlbinval(addr);
}

void pmap_remap_rw(qword addr)
{
    (void)addr;

    set_bits(addr, 3 | (1ULL << 63));
}

void pmap_remap_rwx(qword addr)
{
    (void)addr;

    set_bits(addr, 3);
}

qword pmap_unmap(qword addr)
{
    (void)addr;
    tlbinval(addr);

    qword* pte = get_pte(addr);
    qword pa = *pte & 0x0000fffffffff000;
    *pte = 0;
    // panic("whats unmap for");
    return pa;
}
