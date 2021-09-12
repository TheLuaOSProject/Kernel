#include "drivers/drivers.h"

/**
 * LuaOS Kernel Entry point
 * @param bootloader Stivale2 utilities
 */
void kstart(struct stivale2_struct *bootloader)
{
    struct kernel_console kconsole = setup_console(bootloader);
    
    kconsole.println("LuaOS Kernel v1.0.0");
}