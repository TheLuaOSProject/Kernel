#include <common.h>
#include "drivers/display.h"

/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    struct kernel_console console = setup_console(bootloader);
    
    console.println("Hello, World!");
    
    HANG();
}