#include <common.h>
#include "drivers/display.h"

/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    s2bootloader = bootloader;
    
    kernel_console_t console = setup_console();
    
    HANG();
}