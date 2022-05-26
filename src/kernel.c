#include "common.h"
#include "types.h"

#include "drivers/ports.h"


ATTRIBUTE(noreturn, used)
int kernel_start(struct stivale2_struct *bootloader)
{
    (void)bootloader;
    port.byte.out(124, 3);
}
