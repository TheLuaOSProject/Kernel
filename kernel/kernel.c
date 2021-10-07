#include <common.h>
#include "drivers/drivers.h"
#include "cpu/cpu.h"

/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
//    initialise_screen(bootloader);
    initialise_console(bootloader);
    
    console.set_style(STYLE_BOLD, true);
    console.printfln("\x1b[32mStarted LuaOS v%, built %", LUAOS_VERSION, LUAOS_BUILD_DATE);
    console.printfln("Bootloader brand: %", bootloader->bootloader_brand);
    console.printfln("Bootloader version: %", bootloader->bootloader_version);
    console.set_style(RESET_STYLES, true);
    console.println("---------------------------------");

#ifdef QEMU
    console.print("\x1b[1;93mInitialising logger... ");
    console.set_style(STYLE_BOLD, true);
    initialise_logger();
    console.println("\x1b[32m[Done]");
#endif
    logger.writeln("Started logger");

//    console.print("\x1b[1;93mInitialising GDT... ");
//    console.set_style(STYLE_BOLD, true);
//    initialise_gdt();
//    console.println("\x1b[32m[Done]");
    
    console.print("\x1b[1;93mInitialising IDT... ");
    console.set_style(STYLE_BOLD, true);
    initialise_idt();
    console.println("\x1b[32m[Done]");

    console.print("\x1b[1;93mInitialising framebuffer... ");
    initialise_screen(bootloader);
    string screen_size[2];
    strint(screen.screen_size.x, screen_size[0]);
    strint(screen.screen_size.y, screen_size[1]);
    console.printfln("Screen size: X = %, Y = %", screen_size[0], screen_size[1]);
    console.println("\x1b[32m[Done]");

    console.set_style(RESET_STYLES, true);
    console.println("CPU Info");
    console.printfln("CPU Vendor: %", get_vendor_name());
    console.set_style(STYLE_BOLD, true);
    
    console.print("\x1b[1;93mInitialising keyboard inputs... ");
    console.set_style(STYLE_BOLD, true);
    initialise_keyboard();
    console.println("\x1b[32m[Done]");
    
    
    HANG();
}
