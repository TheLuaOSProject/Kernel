//
// Created by Frityet on 2021-10-08.
//

#ifndef LUAOS_PMM
#define LUAOS_PMM

#include <common.h>

extern struct pmm {
    struct stivale2_struct_tag_memmap *memory_map;
} physical_memory_manager;

void initialise_memory_manager(struct stivale2_struct *bootloader);

#endif //LUAOS_PMM
