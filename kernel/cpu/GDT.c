//
// Created by Frityet on 2021-09-23.
//

#include "GDT.h"

#include "drivers/logger.h"

static struct gdt               table;
static struct gdt_descriptor    descriptor;

void initialise_gdt(void)
{
    logger.writeln("GDT INIT");
    table.null = (struct gdt_entry) {
            .limit0         = 0,
            .base0          = 0,
            .base1          = 0,
            .access_byte    = 0x00,
            .flags          = 0x00,
            .base2          = 0
    };
    
    table.kernel_code = (struct gdt_entry) {
            .limit0         = 0xFFFF,
            .base0          = 0,
            .base1          = 0,
            .access_byte    = 0x9A,
            .flags          = 0x80,
            .base2          = 0
    };

    table.kernel_data = (struct gdt_entry) {
            .limit0         = 0xFFFF,
            .base0          = 0,
            .base1          = 0,
            .access_byte    = 0x92,
            .flags          = 0x80,
            .base2          = 0
    };

    table.user_code = (struct gdt_entry) {
            .limit0         = 0xFFFF,
            .base0          = 0,
            .base1          = 0,
            .access_byte    = 0x92,
            .flags          = 0xCF,
            .base2          = 0
    };

    table.user_data = (struct gdt_entry) {
            .limit0         = 0,
            .base0          = 0,
            .base1          = 0,
            .access_byte    = 0x9A,
            .flags          = 0xA2,
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
    
    descriptor = (struct gdt_descriptor) {
            .limit      = sizeof(table) - 1,
            .offset     = (uint64_t)&table
    };

    LOAD_GDT(&descriptor);
    logger.writeln("DONE");
}

void initialise_tss(uint64_t address)
{
    logger.writeln("TSS INIT");
    table.tss.base0 = address & 0xFFFF;
    table.tss.base1 = (address >> 16) & 0xFF;
    table.tss.base2 = (address >> 24) & 0xFF;
    table.tss.base3 = address >> 32;
    
    asm volatile ("ltr %0" :: "r"((uint16_t)0x28));
    logger.writeln("DONE");
}
