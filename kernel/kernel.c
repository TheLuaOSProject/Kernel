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


/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    initialise_console(bootloader);
    
    console.set_style(STYLE_BOLD, true);
    console.printfln("\x1b[32mStarted LuaOS v%, built %", LUAOS_VERSION, LUAOS_BUILD_DATE);
    console.printfln("Bootloader brand: %", bootloader->bootloader_brand);
    console.printfln("Bootloader version: %", bootloader->bootloader_version);
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

    console.println("\x1b[1;93mInitialising memory manager...");
    initialise_pmm(bootloader);
    console.printfln("Free memory: % bytes free", itoa(physical_memory_manager.get_free_memory(), BASE_10));
 
    console.println("\x1b[1;35mTesting memory...");
    console.println("Allocating 8192 bytes");
    voidptr mem = physical_memory_manager.alloc(2 << 12);
    if (mem == NULL) {
        console.println("\x1b[31mError, alloc returned null!");
        HANG();
    }
    console.println("\x1b[32mSuccess!");
    console.printfln("Free memory: %", itoa(physical_memory_manager.get_free_memory(), BASE_10));
    console.println("\x1b[1;35mFreeing...");
    physical_memory_manager.free(mem, 1024);
    console.println("\x1b[32mSuccess!");
    console.println("\x1b[32m[Done]");
    
    console.print("\x1b[1;93mInitialising IDT... ");
    console.set_style(STYLE_BOLD, true);
    initialise_idt();
    console.println("\x1b[32m[Done]");

    console.println("\x1b[1;93mInitialising framebuffer... ");
    initialise_screen(bootloader);

    string screen_size[2] = {
            itoa(screen.screen_size.x, BASE_10),
            itoa(screen.screen_size.y, BASE_10)
    };
    
    screen.clear_screen(COLOURS_WHITE);

    console.printfln("Screen size: X = %, Y = %", screen_size[0], screen_size[1]);
    console.println("\x1b[32m[Done]");
    
    console.print("\x1b[1;93mInitialising keyboard inputs... ");
    console.set_style(STYLE_BOLD, true);
    initialise_keyboard();
    console.println("\x1b[32m[Done]");


    HANG();
}
