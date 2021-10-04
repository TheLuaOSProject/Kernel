//
// Created by Frityet on 2021-09-20.
//

#include "IDT.h"

#include <drivers/drivers.h>

void idiv_by_zero(struct interrupt_frame *iframe);
void ibreakpoint(struct interrupt_frame *iframe);
void idouble_fault(struct interrupt_frame *iframe);
void igeneral_protection(struct interrupt_frame *iframe);

void asm_div_by_zero();
void asm_breakpoint();
void asm_double_fault();
void asm_general_protection();

static struct idt_gate idt[256];
static struct idt_descriptor descriptor;

void initialise_idt(void)
{
    memset(idt, 0, sizeof(idt));
    
    register_interrupt_handler(0x0,
                               (uint64_t)&asm_div_by_zero,
                               0x8E,
                               0);

    register_interrupt_handler(0x3,
                               (uint64_t)&asm_breakpoint,
                               0x8E,
                               0);

    register_interrupt_handler(0x8,
                               (uint64_t)&asm_double_fault,
                               0x8E,
                               0);

    register_interrupt_handler(0xD,
                               (uint64_t)&asm_general_protection,
                               0x8E,
                               0);
     
    descriptor.size     = sizeof(idt);
    descriptor.offset   = (uint64_t)&idt;

    asm volatile("lidt (%0)" :: "r"(&descriptor));
}

void register_interrupt_handler(uintmax_t   index,
                                uint64_t    address,
                                uint8_t     gate_type,
                                uint8_t     interrupt_stack_table)
{
    idt[index].offset0                  = address & 0xFFFF;
    idt[index].offset1                  = (address >> 16) & 0xFFFF;
    idt[index].offset2                  = address >> 32;
    idt[index].selector                 = 0x08;
    idt[index].type                     = gate_type;
    idt[index].zero                     = 0;
    idt[index].interrupt_stack_table    = interrupt_stack_table;
}

void idiv_by_zero(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;31mERROR: DIVISION BY ZERO");
    HANG();
}

void ibreakpoint(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;34mDEBUG: BREAKPOINT");
    HANG();
}

void idouble_fault(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;31mERROR: DOUBLE FAULT");
    HANG();
}

void igeneral_protection(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;31mERROR");
    HANG();
}
