//
// Created by Frityet on 2022-01-23.
//

#include <stivale2.h>

#include <common.h>

ATTRIBUTE(noreturn, used)
int kernel_start(ATTRIBUTE(unused) struct stivale2_struct *bootloader)
{
    
    HALT();
}
