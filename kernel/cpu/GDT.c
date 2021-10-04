//
// Created by Frityet on 2021-09-23.
//

#include "GDT.h"

static struct gdt               table;
static struct gdt_descriptor    descriptor;

void initialise_gdt(void)
{
    table.null = (struct gdt_entry) {  
        .base2          = 0,
        .access_byte    = 0,
        .base1          = 0,
        .base0          = 0,
        .limit0         = 0,
        .flags          = 0
    };
    
    table.kernel_code = (struct gdt_entry) {
        .limit0         = 0,
        .base0          = 0,
        .base1          = 0,
        .access_byte    = 0x9A,
        .flags          = 0x20,
        .base2          = 0
    };

    table.kernel_data = (struct gdt_entry) {
            .limit0         = 0,
            .base0          = 0,
            .base1          = 0,
            .access_byte    = 0x92,
            .flags          = 0,
            .base2          = 0
    };

    table.user_code = (struct gdt_entry) {
            .limit0         = 0,
            .base0          = 0,
            .base1          = 0,
            .access_byte    = 0xFA,
            .flags          = 0x20,
            .base2          = 0
    };

    table.user_data = (struct gdt_entry) {
            .limit0         = 0,
            .base0          = 0,
            .base1          = 0,
            .access_byte    = 0xF2,
            .flags          = 0,
            .base2          = 0
    };

    table.tss = (struct tss_entry) {
            .limit          = 104,
            .base0          = 0,
            .base1          = 0,
            .flags0         = 0x89,
            .flags1         = 0x20,
            .base2          = 0,
            .base3          = 0,
            .reserved       = 0
    };

    LOAD_GDT(&descriptor);
}

void initialise_tss(uint64_t address)
{
    table.tss.base0 = address & 0xFFFF;
    table.tss.base1 = (address >> 16) & 0xFF;
    table.tss.base2 = (address >> 24) & 0xFF;
    table.tss.base3 = address >> 32;
    
    asm volatile ("ltr %0" :: "r"((uint16_t)0x28));
}
