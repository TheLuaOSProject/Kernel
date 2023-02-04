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

#include "gdt.h"

static void gdt_init(void);

define_module(global_descriptor_table) {
    .initalise = gdt_init
};

static void gdt_init(void)
{
    struct GDTDescriptor *tbl = (void *)global_descriptor_table.table.descriptors;

    // Null
    tbl[0] = (struct GDTDescriptor) {0};

    // Kernel code 16
    tbl[1] = (struct GDTDescriptor) {
        .limit = 0xFFFF,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0x9A,
        .granularity = 0xCF,
        .base_high = 0x00
    };

    // Kernel data 16
    tbl[2] = (struct GDTDescriptor) {
        .limit = 0xFFFF,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0x92,
        .granularity = 0xCF,
        .base_high = 0x00
    };

    // Kernel code 32
    tbl[3] = (struct GDTDescriptor) {
        .limit = 0xFFFF,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0xFA,
        .granularity = 0xCF,
        .base_high = 0x00
    };

    // Kernel data 32
    tbl[4] = (struct GDTDescriptor) {
        .limit = 0xFFFF,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0xF2,
        .granularity = 0xCF,
        .base_high = 0x00
    };

    // Kernel code 64
    tbl[5] = (struct GDTDescriptor) {
        .limit = 0x0,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0x9A,
        .granularity = 0x20,
        .base_high = 0x00
    };

    // Kernel data 64
    tbl[6] = (struct GDTDescriptor) {
        .limit = 0x0,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0x92,
        .granularity = 0,
        .base_high = 0x00
    };

    //These have to be 0, I don't know why
    tbl[7] = (struct GDTDescriptor){0};
    tbl[8] = (struct GDTDescriptor){0};

    // User code 64
    tbl[9] = (struct GDTDescriptor) {
        .limit = 0x0,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0xFA,
        .granularity = 0x20,
        .base_high = 0x00
    };

    // User data 64
    tbl[10] = (struct GDTDescriptor) {
        .limit = 0x0,
        .base_low = 0x0000,
        .base_middle = 0x00,
        .access = 0xF2,
        .granularity = 0,
        .base_high = 0x00
    };

    global_descriptor_table.table.task_state_segment = (struct TSSDescriptor){
        .length = 104 //Why?
    };
}
