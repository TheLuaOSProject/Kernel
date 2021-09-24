//
// Created by Frityet on 2021-09-20.
//

#ifndef LUAOS_IDT
#define LUAOS_IDT

#include <common.h>

#define IDT_TYPE_ATTRIBUTE_INTERRUPT_GATE   0b10001110
#define IDT_TYPE_ATTRIBUTE_CALL_GATE        0b10001100
#define IDT_TYPE_ATTRIBUTE_TRAP_GATE        0b10001111

struct IDT_descriptor_entry {
    uint16_t    offset_0;
    uint16_t    selector;
    uint8_t     interrupt_stack_table;
    uint8_t     type_attribute;
    uint16_t    offset_1;
    uint32_t    offset_2;
    uint32_t    reserved;
};

struct IDT_descriptor {
    uint16_t    limit;
    uint16_t    offset;
} __attribute__((packed));

extern struct IDT_descriptor descriptor;
void initialise_interrupts(void);

void        set_descriptor_entry_offset(struct IDT_descriptor_entry *descriptor_entry, uint64_t offset);
uint64_t    get_descriptor_entry_offset(struct IDT_descriptor_entry *descriptor_entry);


#endif //LUAOS_IDT
