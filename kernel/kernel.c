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
    console.println(CONSOLE_COLOURS_FOREGROUND_GREEN "Started LuaOS v" LUAOS_VERSION ", built " LUAOS_BUILD_DATE "!");
    console.printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Bootloader brand:" CONSOLE_COLOURS_FOREGROUND_GREEN "%", bootloader->bootloader_brand);
    console.printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Bootloader version:" CONSOLE_COLOURS_FOREGROUND_GREEN "%", bootloader->bootloader_version);
    console.println(CONSOLE_COLOURS_FOREGROUND_CYAN "Type sizes:");
    console.printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Byte:"            CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(byte_t)));
    console.printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Word:"            CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(word_t)));
    console.printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Double word:"     CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(doubleword_t)));
    console.printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Quad word:"       CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(quadword_t)));
    console.printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Unsigned long:"   CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(unsigned long)));
    console.set_style(RESET_STYLES, true);
    console.println(CONSOLE_COLOURS_FOREGROUND_DEFAULT "---------------------------------");

     console.set_style(STYLE_BOLD, true);

#ifdef QEMU
    console.print(CONSOLE_COLOURS_FOREGROUND_YELLOW "Initialising logger... ");
    initialise_logger();
    console.println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]");
    logger.writeln("Started logger");
#endif

    console.print(CONSOLE_COLOURS_FOREGROUND_YELLOW "Initialising IDT... ");
    initialise_idt();
    console.println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]");
    
    console.println(CONSOLE_COLOURS_BACKGROUND_YELLOW "Testing interrupts...");
    DEBUG_INTERRUPT();
    console.println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]" CONSOLE_COLOURS_BACKGROUND_DEFAULT);

    console.print(CONSOLE_COLOURS_FOREGROUND_YELLOW "Initialising memory manager... ");
    initialise_pmm(bootloader);
    console.println("Testing allocation...");
    console.println("Allocating 8192 bytes...");
    HALT();
    voidptr_t alloc = physical_memory_manager.memalloc(8192);
    if (alloc == NULL) {
        console.println(CONSOLE_COLOURS_FOREGROUND_RED "Failed to allocate 8192 bytes of memory!");
        HALT();
    }
    physical_memory_manager.free(alloc);
    console.println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]");
    
    console.print(CONSOLE_COLOURS_FOREGROUND_YELLOW "Initialising keyboard inputs... ");
    initialise_keyboard();
    console.println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]");

    HALT();
}
