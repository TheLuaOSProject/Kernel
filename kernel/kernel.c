#include <common.h>
#include "drivers/drivers.h"

/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    initialise_screen(bootloader);
    initialise_console(bootloader);

    point_t pos     = { screen.screen_size.x / 2, screen.screen_size.y / 2 };
    point_t size    = { 128, 256 };
    screen.draw_rect(pos, size, 0x8075FF);
    
    console.printfln("Started LuaOS v%, built %%", LUAOS_VERSION, LUAOS_BUILD_DATE);
    console.printfln("Bootloader brand: %", bootloader->bootloader_brand);
    console.printfln("Bootloader version: %", bootloader->bootloader_version);
    console.println("Written by Amrit Bhogal (Frityet)");
    console.println("Project started in late July 2021");
    
    HANG();
}