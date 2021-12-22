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
#include <string.h>


/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kernel_start(struct stivale2_struct *bootloader)
{
    initialise_console(bootloader);

    console_setstyle(STYLE_BOLD);
    console_println(CONSOLE_COLOURS_FOREGROUND_GREEN "Started LuaOS v" LUAOS_VERSION ", built " LUAOS_BUILD_DATE "!");
    console_printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Bootloader brand:" CONSOLE_COLOURS_FOREGROUND_GREEN "%", bootloader->bootloader_brand);
    console_printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Bootloader version:" CONSOLE_COLOURS_FOREGROUND_GREEN "%", bootloader->bootloader_version);
    console_println(CONSOLE_COLOURS_FOREGROUND_CYAN "Type sizes:");
    console_printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Byte:"            CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(byte_t)));
    console_printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Word:"            CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(word_t)));
    console_printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Double word:"     CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(doubleword_t)));
    console_printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Quad word:"       CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(quadword_t)));
    console_printfln(CONSOLE_COLOURS_FOREGROUND_YELLOW "Unsigned long:"   CONSOLE_COLOURS_FOREGROUND_GREEN "%",   STRDEC(sizeof(unsigned long)));
    console_setstyle(RESET_STYLES);
    console_println(CONSOLE_COLOURS_FOREGROUND_DEFAULT "---------------------------------");
    console_setstyle(STYLE_BOLD);

#ifdef QEMU
    logger_writeln("Started logger");
#endif

    console_print(CONSOLE_COLOURS_FOREGROUND_YELLOW "Initialising IDT... ");
    initialise_idt();
    console_println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]");
    
    console_println(CONSOLE_COLOURS_FOREGROUND_YELLOW "Testing interrupts...");
    DEBUG_INTERRUPT();
    console_println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]");

    console_print(CONSOLE_COLOURS_FOREGROUND_YELLOW "Initialising memory manager... ");
    initialise_pmm(bootloader);
//    CRASH();
    console_println("Testing allocation...");
    console_println("Allocating 8192 bytes...");
    var alloc = pmm_memalloc(8192);
    if (alloc == NULL) {
        console_println(CONSOLE_COLOURS_FOREGROUND_RED "Failed to allocate 8192 bytes of memory!");
        HALT();
    }
    pmm_free(alloc);
    console_println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]");
    
    console_print(CONSOLE_COLOURS_FOREGROUND_YELLOW "Initialising keyboard inputs... ");
    initialise_keyboard();
    console_println(CONSOLE_COLOURS_FOREGROUND_GREEN "[Done]");
    
    
    HALT();
}
