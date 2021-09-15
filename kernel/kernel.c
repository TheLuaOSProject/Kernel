#include <common.h>
#include "drivers/console.h"

/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    struct kernel_console console = setup_console(bootloader);
    
    console.printfln("\x1b[1;32mStarted LuaOS v%, built %%", LUAOS_VERSION, LUAOS_BUILD_DATE);
    console.printfln("\x1b[1;0mBootloader brand: %", bootloader->bootloader_brand);
    console.printfln("Bootloader version: %", bootloader->bootloader_version);
    console.println("Written by Amrit Bhogal (Frityet)");
    console.println("Project started in late July 2021");
    console.clear();
    HANG();
}