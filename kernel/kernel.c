#include "drivers/drivers.h"

// The following will be our kernel's entry point.
void kstart(struct stivale2_struct *bootloader)
{
    struct kernel_console kconsole = setup_console(bootloader);
    
    kconsole.println("LuaOS Kernel v1.0.0");
}