//
// Created by Frityet on 2022-01-23.
//

#include <utilities.h>

ATTRIBUTE(noreturn)
ATTRIBUTE(used)
int kernel_start(ATTRIBUTE(unused) struct stivale2_struct *bootloader)
{
    HALT();
}
