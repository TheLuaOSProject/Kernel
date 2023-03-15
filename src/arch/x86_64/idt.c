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

extern void int_div_by_zero(void *);
extern void int_breakpoint(void *);
extern void int_double_fault(void *);
extern void int_general_protection(void *);
extern void int_debug(void *);
extern void int_invalid_opcode(void *);


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

    asm("LIDT %0" :: "m"(idtr));
}

void idt_register_int(byte int_no, void(*routine)(void *))
{
    if (int_no > 255) {
        error("Interrupt number {} is too large", int_no);
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

[[gnu::always_inline]]
static inline void print_cpu_info(CPUContext ctx)
{
    info("CPU Info");
    info("\nRAX: {} | RBX: {} | RCX: {} | RDX: {} | RSI: {} | RDI: {} |\n"
         "R8:  {} | R9: {} | R10: {} | R11: {} | R12: {} | R13: {} | R14: {} | R15: {} |\n"
         "RBP: {} | RSP: {} | RIP: {} | RFLAGS: {}\n",
         (void *)ctx.rax, (void *)ctx.rbx, (void *)ctx.rcx, (void *)ctx.rdx, (void *)ctx.rsi, (void *)ctx.rdi,
         (void *)ctx.r8, (void *)ctx.r9, (void *)ctx.r10, (void *)ctx.r11, (void *)ctx.r12, (void *)ctx.r13, (void *)ctx.r14, (void *)ctx.r15,
         (void *)ctx.rbp, (void *)ctx.rsp, (void *)ctx.rip, (void *)ctx.rflags);
}

// I should have frames, and maybe a more efficent method than this?
void div_by_zero_handler(CPUContext *cpu)
{
    panic("Divide by zero");
    print_cpu_info(*cpu);
}

void breakpoint_handler(CPUContext *cpu)
{
    panic("Breakpoint");
    print_cpu_info(*cpu);
}

void double_fault_handler(CPUContext *cpu)
{
    error("Double fault");
    print_cpu_info(*cpu);
}

void general_protection_handler(CPUContext *cpu)
{
    error("General protection fault");
    print_cpu_info(*cpu);
}

void debug_handler(CPUContext *cpu)
{
    panic("Debug");
    print_cpu_info(*cpu);
}

void invalid_opcode_handler(CPUContext *cpu)
{
    panic("Invalid opcode");
    print_cpu_info(*cpu);
}
