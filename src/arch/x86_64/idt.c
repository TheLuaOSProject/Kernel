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

#include "luck/arch/x86_64/idt.h"
#include "luck/arch/x86_64/cpu.h"

#include "luck/io/log.h"

attribute(interrupt) void int_div_by_zero(void *);
attribute(interrupt) void int_breakpoint(void *);
attribute(interrupt) void int_double_fault(void *);
attribute(interrupt) void int_general_protection(void *);
attribute(interrupt) void int_debug(void *);
attribute(interrupt) void int_invalid_opcode(void *);


static struct IDTEntry idt[256];
static struct IDTRegister idtr = {
    .limit = sizeof(struct IDTEntry) * 256 - 1,
    .base = (qword)idt,
};

void idt_init()
{
    idt_register_int(0x0, int_div_by_zero);
    idt_register_int(0x3, int_breakpoint);
    idt_register_int(0x8, int_double_fault);
    idt_register_int(0xD, int_general_protection);
    idt_register_int(0x1, int_debug);
    idt_register_int(0x6, int_invalid_opcode);

    asm volatile("LIDT %0" :: "m"(idtr));
}

void idt_register_int(byte int_no, attribute(interrupt) void(*routine)(void *))
{
    if (int_no > 255) {
        error("Interrupt number {} is too large", int_no);
        return;
    }

    if (routine == nullptr) {
        error("Interrupt routine {} is NULL", (uintptr_t)routine);
        return;
    }

    qword handler = (qword)routine;
    idt[int_no] = (struct IDTEntry) {
        .offset_low = (dword)handler,
        .selector = 0x28,
        .interrupt_stack_table = 0,
        .flags = 0x8E,
        .offset_middle = handler >> 16,
        .offset_high = handler >> 32,
        .reserved = 0
    };
    debug("  Registered interrupt {}", int_no);
}

// I should have frames, and maybe a more efficent method than this?
void div_by_zero_handler()
{
    panic("Divide by zero");
}

void breakpoint_handler()
{
    panic("Breakpoint");
}

void double_fault_handler()
{
    panic("Double fault");
}

void general_protection_handler()
{
    panic("General protection fault");
}

void debug_handler()
{
    panic("Debug");
}

void invalid_opcode_handler()
{
    panic("Invalid opcode");
}
