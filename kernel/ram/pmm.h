/**
 * @file    pmm.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Physical memory manager, allows for the allocation of pages
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */
#ifndef LUAOS_PMM
#define LUAOS_PMM

#include <common.h>

#define PAGE_SIZE               (2 << 11)
#define PHYSICAL_BASE_ADDRESS   0xffff800000000000

extern struct pmm {
    struct stivale2_mmap_entry  *memory_map;
    uint64_t                    memory_map_entry_count;
    voidptr                     (*alloc)(size_t size);
    void                        (*free)(voidptr ptr, size_t size);
    uint64_t                    (*get_free_memory)(void);
} physical_memory_manager;

void initialise_pmm(struct stivale2_struct *bootloader);

static voidptr alloc(size_t size);
static void free(voidptr ptr, size_t size);
static uint64_t get_free_memory(void);


#endif //LUAOS_PMM
