//
// Created by Frityet on 2021-10-08.
//

#include "pmm.h"
#include "drivers/logger.h"
#include <string.h>
#include <common.h>
#include "bitmap.h"
#include "lock.h"

#include <drivers.h>

static voidptr_t memalloc(size_t size);
static void free(voidptr_t ptr);
static uint64_t get_free_memory(void);

struct pmm physical_memory_manager;

static lock_t memlock = 0;

void initialise_pmm(struct stivale2_struct *bootloader)
{
    struct stivale2_struct_tag_memmap *tag = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_MEMMAP_ID);

    physical_memory_manager = (struct pmm) {
        .memory_map             = tag->memmap,
        .memory_map_entry_count = tag->entries,

        .get_free_memory        = get_free_memory,
        .memalloc               = memalloc,
        .free                   = free,
    }; 

    for (size_t i = 0; i < physical_memory_manager.memory_map_entry_count; ++i) {
        struct stivale2_mmap_entry mmap_entry = physical_memory_manager.memory_map[i];
        logger.writef("Memory map entry % ", itoa(i, BASE_10));
        logger.writefln("of % loaded!", itoa(physical_memory_manager.memory_map_entry_count, BASE_10));
        if (mmap_entry.type != STIVALE2_MMAP_USABLE
            && mmap_entry.type != STIVALE2_MMAP_KERNEL_AND_MODULES)
            continue;
        
        quadword_t top_page = mmap_entry.base + mmap_entry.length;
        
        if (physical_memory_manager.last_page < top_page)
            physical_memory_manager.last_page = top_page;
    }

    physical_memory_manager.bitmap_size = ROUND_DIV(physical_memory_manager.last_page / PAGE_SIZE, 8);

    for (size_t i = 0; i < physical_memory_manager.memory_map_entry_count; ++i) {
        struct stivale2_mmap_entry mmap_entry = physical_memory_manager.memory_map[i];
        if  ((mmap_entry.type != STIVALE2_MMAP_USABLE && mmap_entry.type != STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE) 
            || mmap_entry.length < physical_memory_manager.bitmap_size)
            continue;

        physical_memory_manager.bitmap = (byte_t *)mmap_entry.base + PHYSICAL_BASE_ADDRESS;
        uint64_t page_count = ROUND_DIV(physical_memory_manager.bitmap_size, PAGE_SIZE);

        memset(physical_memory_manager.bitmap, 0xFF, physical_memory_manager.bitmap_size);

        uint64_t coefficient = page_count * PAGE_SIZE;
        mmap_entry.base     += coefficient;
        mmap_entry.length   -= coefficient;
        break;
    }

    for (size_t i = 0; i < physical_memory_manager.memory_map_entry_count; ++i) {
        struct stivale2_mmap_entry mmap_entry = physical_memory_manager.memory_map[i];
        if  (mmap_entry.type    != STIVALE2_MMAP_USABLE
          && mmap_entry.type    != STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE)
            continue;
        
        uint64_t pagenum = mmap_entry.base / PAGE_SIZE;

        //Mark frames as free
        uint64_t length = mmap_entry.length / PAGE_SIZE;
        logger.writefln("Set bitmap bit % to free", STRDEC(i));
        for (size_t j = pagenum; j <= pagenum + length; ++j) {
            clear_bit(physical_memory_manager.bitmap, j);
        }
    }
}

static voidptr_t memalloc_raw(size_t size)
{
    size_t count = 0;

    acquire_lock(&memlock);

    for (size_t i = 0; i < physical_memory_manager.bitmap_size * 8; ++i) {
        if (!test_bit(physical_memory_manager.bitmap, i)) {
            ++count;

            if (count == size) {
                quadword_t page = i - size + 1;

                for (quadword_t j = page; j < page + size; ++j) 
                    set_bit(physical_memory_manager.bitmap, j);
                
                quadword_t address = page * PAGE_SIZE;
                memset((voidptr_t)address + PHYSICAL_BASE_ADDRESS, 0, count * PAGE_SIZE);

                release_lock(&memlock);

                return (voidptr_t)address;
            }
        } else {
            count = 0;
        }
    }

    release_lock(&memlock);

    return NULL;
}

static voidptr_t memalloc(size_t size)
{
    struct allocation_header *alloc = memalloc_raw(sizeof(*alloc) + size);
    alloc->size = size;
    alloc->data = alloc + 1;
    return alloc;
}

static void free(voidptr_t ptr)
{
    struct allocation_header *alloc = headerof(ptr);
    if (alloc->data != ptr) {
        console.printfln("\x1b[31m Could not free pointer at %", STRHEX((int64_t)ptr));
    }
    quadword_t page = (quadword_t)alloc / PAGE_SIZE;

    acquire_lock(&memlock);

    for (uint64_t i = page; i < page + alloc->size; ++i)
        clear_bit(physical_memory_manager.bitmap, i);

    release_lock(&memlock);
}

static uint64_t get_free_memory(void)
{
    logger.writeln("Getting free memory...");
    uint64_t pagecount = 0;

    logger.writefln("BITMAP SIZE: %", STRDEC(physical_memory_manager.bitmap_size));
    
    for (size_t i = 0; i < physical_memory_manager.bitmap_size * 8; ++i) {
        if (!test_bit(physical_memory_manager.bitmap, i)) {
            ++pagecount;
        }
    }
    
    uint64_t ret = pagecount * PAGE_SIZE;
    
    logger.writefln("Total size: %", STRDEC(ret));

    return ret;
}
