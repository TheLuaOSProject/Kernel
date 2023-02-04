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

static void init(), register_int(byte int_no, void *routine, byte flags), load(void);

extern void int_div_by_zero(),
            int_breakpoint(),
            int_double_fault(),
            int_general_protection(),
            int_debug(),
            int_invalid_opcode();

extern void load_idt();

define_module(interrupts) {
    .initalise = init,
    .register_interrupt = register_int,
    .load = load
};

static void init()
{
    log.print("Initialising interrupts\n");
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

    if (flags > 7) {
        log.error("Interrupt flags are too large");
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
}

static void load()
{
    log.info("Registering interrupt \"div_by_zero\"");
    register_int(0, &int_div_by_zero, 0);
}

//handler

void div_by_zero_handler()
{
    log.error("Divide by zero");
}
