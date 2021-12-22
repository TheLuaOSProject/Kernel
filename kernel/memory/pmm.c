//
// Created by Frityet on 2021-10-08.
//

#include "pmm.h"
#include <drivers/logger.h>
#include <string.h>
#include <common.h>
#include <bitmap.h>
#include <lock.h>
#include <iso646.h>

struct pmm physical_memory_manager;

static lock_t memlock = 0;

void initialise_pmm(struct stivale2_struct *bootloader)
{
    logger_writeln("Initialising PMM");
    struct stivale2_struct_tag_memmap *tag = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_MEMMAP_ID);

    physical_memory_manager = (struct pmm) {
        .memory_map             = tag->memmap,
        .memory_map_entry_count = tag->entries,
    };

    for (size_t i = 0; i < physical_memory_manager.memory_map_entry_count; ++i) {
        var entry = physical_memory_manager.memory_map[i];

        logger_writefln("Memory map entry %/% found", STRDEC(i), STRDEC(physical_memory_manager.memory_map_entry_count));
        
        if (entry.type != STIVALE2_MMAP_USABLE 
        &&  entry.type != STIVALE2_MMAP_KERNEL_AND_MODULES)
            continue;
        
        quadword_t top_page = entry.base + entry.length;
        
        if (physical_memory_manager.last_page < top_page)
            physical_memory_manager.last_page = top_page;
    }
    
    physical_memory_manager.bitmap_size = round_division(physical_memory_manager.last_page / PAGE_SIZE, 8);
    logger_writefln("Bitmap size: %", STRDEC(physical_memory_manager.bitmap_size));

    for (size_t i = 0; i < physical_memory_manager.memory_map_entry_count; ++i) {
        struct stivale2_mmap_entry *entry = &physical_memory_manager.memory_map[i];

        if ((entry->type not_eq STIVALE2_MMAP_USABLE and entry->type not_eq STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE) 
            && entry->length < physical_memory_manager.bitmap_size)
            continue;
        
        physical_memory_manager.bitmap = (byte_t *)entry->base + PHYSICAL_BASE_ADDRESS;
        size_t page_count = round_division(physical_memory_manager.bitmap_size, PAGE_SIZE);

        //Set the value of the bitmap to 0xFF (used or smth like that idk man im tired)
        memset(physical_memory_manager.bitmap, 0xFF, physical_memory_manager.bitmap_size);
        
        uint64_t mul = page_count * PAGE_SIZE;
        entry->base         += mul;
        entry->length       -= mul;
        logger_writeln("Set bitmap");
        break;
    }

    for (size_t i = 0; i < physical_memory_manager.bitmap_size; ++i) {
        var entry = physical_memory_manager.memory_map[i];
        
        uint64_t    base    = entry.base / PAGE_SIZE,
                    len     = entry.length / PAGE_SIZE;

        for (size_t j = base; j < base + len; ++j) {
            clear_bit(physical_memory_manager.bitmap, j);
        }
    }
}

static voidptr_t memalloc_raw(size_t size)
{
    size_t count = 0;
    
    logger_writefln("Allocating % bytes of memory", STRDEC(size));

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
    
    logger_writeln("Allocation failed!");
    return NULL;
}

voidptr_t pmm_memalloc(size_t size)
{
    struct allocation_header *alloc = memalloc_raw(sizeof(*alloc) + size);
    alloc->size = size;
    alloc->data = alloc + 1;
    return alloc;
}

void pmm_free(voidptr_t ptr)
{
    struct allocation_header *alloc = headerof(ptr);
    if (alloc->data != ptr) {
        logger_writefln("Could not free pointer at %", STRHEX((int64_t)ptr));
        return;
    }
    quadword_t page = (quadword_t)alloc / PAGE_SIZE;

    acquire_lock(&memlock);

    for (uint64_t i = page; i < page + alloc->size; ++i)
        clear_bit(physical_memory_manager.bitmap, i);

    release_lock(&memlock);
}

size_t get_free_memory(void)
{
    logger_writeln("Getting free memory...");
    uint64_t pagecount = 0;
    
    for (size_t i = 0; i < physical_memory_manager.bitmap_size * 8; ++i) {
        if (!test_bit(physical_memory_manager.bitmap, i)) {
            ++pagecount;
        }
    }
    
    size_t ret = pagecount * PAGE_SIZE;
    
    logger_writefln("Total size: %", STRDEC(ret));

    return ret;
}
