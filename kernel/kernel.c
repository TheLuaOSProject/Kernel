#include <common.h>
#include "drivers/drivers.h"
#include "cpu/cpu.h"

/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    initialise_screen(bootloader);
    initialise_console(bootloader);
    
    
    console.set_style(STYLE_BOLD, true);
    console.printfln("\x1b[32mStarted LuaOS v%, built %", LUAOS_VERSION, LUAOS_BUILD_DATE);
    console.set_style(RESET_STYLES, true);
    console.printfln("Bootloader brand: %", bootloader->bootloader_brand);
    console.printfln("Bootloader version: %", bootloader->bootloader_version);
    console.set_style(STYLE_BOLD, true);
    console.println("---------------------------------");
    
    
    string_t screen_size[2];
    strint(screen.screen_size.x, screen_size[0]);
    strint(screen.screen_size.y, screen_size[1]);
     
    console.printfln("Screen size: X = %, Y = %", screen_size[0], screen_size[1]);

    HANG();
}
