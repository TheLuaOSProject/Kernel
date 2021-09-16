#include <common.h>
#include "drivers/drivers.h"

/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    struct kernel_console console = setup_console(bootloader);
    
    console.printfln("Started LuaOS v%, built %%", LUAOS_VERSION, LUAOS_BUILD_DATE);
    console.printfln("Bootloader brand: %", bootloader->bootloader_brand);
    console.printfln("Bootloader version: %", bootloader->bootloader_version);
    console.println("Written by Amrit Bhogal (Frityet)");
    console.println("Project started in late July 2021");
    
    HANG();
}