/**
 * @file    kernel.c
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Entry point of the kernel
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */

#include <common.h>
#include <components.h>
#include <drivers.h>
#include <components.h>
#include <string.h>


/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    initialise_console(bootloader);
    
    console.set_style(STYLE_BOLD, true);
    console.println("\x1b[32mStarted LuaOS v" LUAOS_VERSION ", built " LUAOS_BUILD_DATE);
    console.printfln("Bootloader brand: %", bootloader->bootloader_brand);
    console.printfln("Bootloader version: %", bootloader->bootloader_version);
    console.println("Type sizes:");
    console.printfln("Byte: %",             STRDEC(sizeof(byte_t)));
    console.printfln("Word: %",             STRDEC(sizeof(word_t)));
    console.printfln("Double word: %",      STRDEC(sizeof(dword_t)));
    console.printfln("Quad word: %",        STRDEC(sizeof(qword_t)));
    console.printfln("Unsigned long: %",    STRDEC(sizeof(unsigned long)));
    console.set_style(RESET_STYLES, true);
    console.println("---------------------------------");


    console.print("\x1b[1;93mInitialising logger... ");
    console.set_style(STYLE_BOLD, true);
#ifdef QEMU
    initialise_logger();
#endif
    console.println("\x1b[32m[Done]");

    logger.writeln("Started logger");

    //get_vendor_name();

//    console.print("\x1b[1;93mInitialising GDT... ");
//    console.set_style(STYLE_BOLD, true);
//    initialise_gdt();
//    console.println("\x1b[32m[Done]");

    console.print("\x1b[1;93mInitialising memory manager... ");
    initialise_pmm(bootloader);
    console.println("Testing allocation...");
    console.println("Allocating 8192 bytes...");
    voidptr_t alloc = physical_memory_manager.memalloc(8192);
    if (alloc == NULL) {
        console.println("Failed to allocate 8192 bytes of memory!");
        HALT();
    }
    physical_memory_manager.free(alloc);
    console.println("\x1b[32m[Done]");
    
    console.print("\x1b[1;93mInitialising IDT... ");
    console.set_style(STYLE_BOLD, true);
    initialise_idt();
    console.println("\x1b[32m[Done]");

    console.print("\x1b[1;93mInitialising PMM... ");
    console.set_style(STYLE_BOLD, true);
    initialise_pmm(bootloader);
    
    console.print("\x1b[1;93mInitialising keyboard inputs... ");
    console.set_style(STYLE_BOLD, true);
    initialise_keyboard();
    console.println("\x1b[32m[Done]");

    HALT();
}
