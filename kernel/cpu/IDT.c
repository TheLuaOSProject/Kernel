//
// Created by Frityet on 2021-09-20.
//

#include "IDT.h"

struct IDT_descriptor descriptor;
void initialise_interrupts(void)
{
    
}

void set_descriptor_entry_offset(struct IDT_descriptor_entry *descriptor_entry, uint64_t offset)
{
    descriptor_entry->offset_0 = (uint16_t)(offset & 0x000000000000ffff);
    descriptor_entry->offset_1 = (uint16_t)((offset & 0x00000000ffff0000) >> 16);
    descriptor_entry->offset_2 = (uint16_t)((offset & 0xffffffff00000000) >> 32);
}

uint64_t get_descriptor_entry_offset(struct IDT_descriptor_entry *descriptor_entry)
{
    uint64_t offset = 0;
    offset |= (uint64_t)descriptor_entry->offset_0;
    offset |= (uint64_t)descriptor_entry->offset_1 << 16;
    offset |= (uint64_t)descriptor_entry->offset_2 << 32;
    return offset;
}
