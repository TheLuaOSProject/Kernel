//
// Created by Frityet on 2021-10-08.
//

#include "pmm.h"
#include "drivers/logger.h"
#include <common.h>

struct pmm physical_memory_manager;

void initialise_pmm(struct stivale2_struct *bootloader)
{
    struct stivale2_struct_tag_memmap *tag = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_MEMMAP_ID);
    physical_memory_manager.memory_map = tag->memmap;
    physical_memory_manager.memory_map_entry_count = tag->entries;


}
