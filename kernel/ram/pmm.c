//
// Created by Frityet on 2021-10-08.
//

#include "pmm.h"
#include "drivers/logger.h"

struct pmm physical_memory_manager;

uintptr_t    top_page = 0;
uint8_t      *bitmap;


void initialise_memory_manager(struct stivale2_struct *bootloader)
{
    logger.writeln("Initialising Physical Memory Manager");

    {
        struct stivale2_struct_tag_memmap *tag = (struct stivale2_struct_tag_memmap *) get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_MEMMAP_ID);
        physical_memory_manager.memory_map = tag->memmap;
        physical_memory_manager.entry_count = tag->entries;
    }

    logger.writeln("Setting top page");
    //Set top page
    for (int i = 0; i < physical_memory_manager.entry_count; ++i) {
        struct stivale2_mmap_entry entry = physical_memory_manager.memory_map[i];
        /*
        string  index   = strnum(i, BASE_10),
                base    = strnum(entry.base, BASE_16),
                length  = strnum(entry.length, BASE_10),
                type    = strnum(entry.type, BASE_10);

        logger.writefln("Memory Map Entry %", index);
        logger.writefln("Base:      %", base);
        logger.writefln("Length:    %", length);
        logger.writefln("Type:      %", type);
         */
        if (entry.type != STIVALE2_MMAP_USABLE
        &&  entry.type != STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE
        &&  entry.type != STIVALE2_MMAP_KERNEL_AND_MODULES)
            continue;

        uintptr_t top = entry.base + entry.length;
        if (top > top_page) {
            top_page = top;
        }
    }

    logger.writefln("Initalising bitmap");
    //Set bitmap
    size_t bitmap_size = ROUND_UP(top_page / PAGE_SIZE, 8);
    for (int i = 0; i < physical_memory_manager.entry_count; ++i) {
        struct stivale2_mmap_entry entry = physical_memory_manager.memory_map[i];
        if (entry.type != STIVALE2_MMAP_USABLE || entry.length < bitmap_size)
            continue;


        bitmap = (uint8_t *)entry.base + PHYSICAL_BASE_ADDRESS;
        size_t bm_pages = ROUND_UP(bitmap_size, PAGE_SIZE);

        memset(bitmap, 0xFF, bitmap_size);

        //Val not ref
        physical_memory_manager.memory_map[i].base   += bm_pages * PAGE_SIZE;
        physical_memory_manager.memory_map[i].length -= bm_pages * PAGE_SIZE;
        break;
    }

    logger.writeln("Populating Bitmap");
    //Populate bitmap
    for (int i = 0; i < physical_memory_manager.entry_count; ++i) {
        struct stivale2_mmap_entry entry = physical_memory_manager.memory_map[i];
        if (entry.type != STIVALE2_MMAP_USABLE)
            continue;

        size_t  page_num    = entry.base / PAGE_SIZE,
                length      = entry.length / PAGE_SIZE;

        for (size_t j = page_num; j <= page_num + length; ++j) {
            CLEAR_BIT(bitmap, j);
        }
    }

    physical_memory_manager.allocate = &allocate;

    logger.writeln("Done");
}

static voidptr allocate(size_t size)
{
    size_t count = 0;

    for (int i = 0; i < b; ++i) {
        
    }
}
