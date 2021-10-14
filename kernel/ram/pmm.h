//
// Created by Frityet on 2021-10-08.
//

#ifndef LUAOS_PMM
#define LUAOS_PMM

#include <common.h>

#define PAGE_SIZE               (2 << 11)
#define PHYSICAL_BASE_ADDRESS   0xffff800000000000

extern struct pmm {
    struct stivale2_mmap_entry  *memory_map;
    uint32_t                    entry_count;
    uintptr_t                   top_page;
    uint8_t                     *bitmap;
    size_t                      bitmap_size;
    voidptr                     (*allocate)(size_t size);
} physical_memory_manager;

void initialise_memory_manager(struct stivale2_struct *bootloader);

static voidptr allocate(size_t size);

#endif //LUAOS_PMM
