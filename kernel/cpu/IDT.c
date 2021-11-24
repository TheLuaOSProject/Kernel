//
// Created by Frityet on 2021-09-20.
//

#include "idt.h"

#include <drivers.h>

void div_by_zero_i(struct interrupt_frame *iframe);
void breakpoint_i(struct interrupt_frame *iframe);
void double_fault_i(struct interrupt_frame *iframe);
void general_protection_i(struct interrupt_frame *iframe);
void debug_i(struct interrupt_frame *iframe);
void invalid_opcode_i(struct interrupt_frame *iframe);

extern void LOAD_IDT(struct idt_descriptor *descriptor);

extern void ASM_DIV_BY_ZERO();
extern void ASM_BREAKPOINT();
extern void ASM_DOUBLE_FAULT();
extern void ASM_GENERAL_PROTECTION();
extern void ASM_DEBUG();
extern void ASM_INVALID_OPCODE();

static struct idt_gate          interrupt_descriptor_table[256];
static struct idt_descriptor    descriptor;

void initialise_idt(void)
{
    logger.writeln("IDT INIT");
    memset(interrupt_descriptor_table, 0, sizeof(interrupt_descriptor_table));
    
    register_interrupt_handler(0x0,
                               (uint64_t) &ASM_DIV_BY_ZERO,
                               0x8E,
                               0);

    register_interrupt_handler(0x3,
                               (uint64_t) &ASM_BREAKPOINT,
                               0x8E,
                               0);

    register_interrupt_handler(0x72,
                               (uint64_t) &ASM_DEBUG,
                               0x8E,
                               0);

    register_interrupt_handler(0x8,
                               (uint64_t) &ASM_DOUBLE_FAULT,
                               0x8E,
                               0);

    register_interrupt_handler(0xD,
                               (uint64_t) &ASM_GENERAL_PROTECTION,
                               0x8E,
                               0);

    register_interrupt_handler(0x6,
                               (uint64_t)&ASM_INVALID_OPCODE,
                               0x8E,
                               0);
     
    descriptor.limit    = sizeof(interrupt_descriptor_table) - 1;
    descriptor.offset   = (uint64_t)&interrupt_descriptor_table;

    LOAD_IDT(&descriptor);
    logger.writeln("DONE");
}

void register_interrupt_handler(uintmax_t   index,
                                uint64_t    address,
                                uint8_t     gate_type,
                                uint8_t     interrupt_stack_table)
{
    if (index > 255)
    {
        console.println("\x1b[31mYou actual fucking dumbass, IDT entries cannot be over 255 you genuine fucking idiot");
        return;
    }
    
    interrupt_descriptor_table[index].offset0                  = address & 0xFFFF;
    interrupt_descriptor_table[index].offset1                  = (address >> 16) & 0xFFFF;
    interrupt_descriptor_table[index].offset2                  = address >> 32;
    interrupt_descriptor_table[index].selector                 = 0x28;
    interrupt_descriptor_table[index].type                     = gate_type;
    interrupt_descriptor_table[index].zero                     = 0;
    interrupt_descriptor_table[index].interrupt_stack_table    = interrupt_stack_table;
}

void div_by_zero_i(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;31mERROR: DIVISION BY ZERO");
    HANG();
}

void breakpoint_i(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;34mDEBUG: BREAKPOINT");
    HANG();
}

void double_fault_i(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;31mERROR: DOUBLE FAULT");
    HANG();
}

void general_protection_i(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;31mERROR");
    HANG();
}

void debug_i(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;34mDEBUG: Interrupt 0x72 called!");
    return;
}

void invalid_opcode_i(struct interrupt_frame *iframe)
{
    console.println("\x1b[1;31mINVALID OPCODE");
    HANG();
}
