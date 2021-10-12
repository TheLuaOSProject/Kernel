//
// Created by Frityet on 2021-10-08.
//

#include "pmm.h"
#include "drivers/logger.h"
#include "drivers/console.h"

struct pmm physical_memory_manager;

void initialise_memory_manager(struct stivale2_struct *bootloader)
{
    logger.writeln("Initialising Physical Memory Manager");

    physical_memory_manager.memory_map = (struct stivale2_struct_tag_memmap *) get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_MEMMAP_ID);
    for (int i = 0; i < physical_memory_manager.memory_map->entries; ++i) {
        struct stivale2_mmap_entry entry = physical_memory_manager.memory_map->memmap[i];
        string  index   = strnum(i, BASE_10),
                base    = strnum(entry.base, BASE_16),
                length  = strnum(entry.length, BASE_10),
                type    = strnum(entry.type, BASE_10);

        logger.writefln("Memory Map Entry #%", index);
        logger.writefln("Base:      %", base);
        logger.writefln("Length:    %", length);
        logger.writefln("Type:      %", type);
    }
    logger.writeln("Done");
}
