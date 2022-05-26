#include "common.h"
#include "types.h"


ATTRIBUTE(noreturn, used)
int kernel_start(struct stivale2_struct *bootloader)
{
    (void)bootloader;
}
