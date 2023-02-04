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

#include "interrupts.h"

#include "io/log.h"
#include "io/console.h"

static void init(), register_int(byte int_no, void *routine, byte flags), load(void);

extern void int_div_by_zero(),
            int_breakpoint(),
            int_double_fault(),
            int_general_protection(),
            int_debug(),
            int_invalid_opcode();

define_module(interrupts) {
    .initalise = init,
    .register_interrupt = register_int,
    .load = load,
    .iregister = {
        .limit = sizeof(struct IDTEntry) * 256 - 1,
        .base = (uint64_t)&interrupts.descriptor_table
    },
};

static void init()
{
    log.print("Initialising interrupts\n");

    register_int(0x0, int_div_by_zero, 0x8E);
    register_int(0x3, int_breakpoint, 0x8E);
    register_int(0x8, int_double_fault, 0x8E);
    register_int(0xD, int_general_protection, 0x8E);
    register_int(0x1, int_debug, 0x8E);
    register_int(0x6, int_invalid_opcode, 0x8E);

    load();

    log.info("Done");
}

static void register_int(byte int_no, void *routine, byte flags)
{
    if (int_no > 255) {
        log.error("Interrupt number is too large");
        return;
    }

    if (routine == nullptr) {
        log.error("Interrupt routine is NULL");
        return;
    }

    uint64_t handler = (uint64_t)routine;
    interrupts.descriptor_table[int_no] = (struct IDTEntry) {
        .offset_low = (uint16_t)handler,
        .selector = 0x28,
        .interrupt_stack_table = 0,
        .flags = flags,
        .offset_middle = handler >> 16,
        .offset_high = handler >> 32,
        .reserved = 0
    };
    log.info("Registered interrupt");
}

static void load()
{
    log.info("Loading interrupts");
    asm volatile ("LIDT %0" :: "m"(interrupts.iregister));
}

// I should have frames, and maybe a more efficent method than this?
void div_by_zero_handler()
{
    log.error("Divide by zero");
}

void breakpoint_handler()
{
    log.error("Breakpoint");
    console.info("DEBUG: Breakpoint");
}

void double_fault_handler()
{
    log.fatal("Double fault");
    console.fatal("Double fault");
}

void general_protection_handler()
{
    log.error("General protection fault");
    console.error("General protection fault");
}

void debug_handler()
{
    log.error("Debug");
}

void invalid_opcode_handler()
{
    log.error("Invalid opcode");
}
