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
    voidptr                     (*alloc)(size_t size);
    void                        (*free)(voidptr ptr, size_t size);
    uint64_t                    (*get_free_memory)(void);
} physical_memory_manager;

void initialise_pmm(struct stivale2_struct *bootloader);

static voidptr alloc(size_t size);
static void free(voidptr ptr, size_t size);
static uint64_t get_free_memory(void );

inline void clear_bit(uint8_t *bitmap, uintptr_t bit);
inline bool is_bit_set(const uint8_t *bitmap, uintptr_t bit);
inline void set_bit(uint8_t *bitmap, uintptr_t bit);


#endif //LUAOS_PMM
