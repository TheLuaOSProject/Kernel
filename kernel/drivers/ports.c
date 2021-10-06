//
// Created by Frityet on 2021-09-16.
//

#include "ports.h"

uint8_t port_in(uint16_t port)
{
    uint8_t res;

    asm (
        "in %%dx, %%al": 
        "=a" (res):
        "d" (port)
    );
    
    return res;
}

void port_out(uint16_t port, uint8_t data)
{
    asm (
        "out %%al, %%dx" ::
        "a" (data),
        "d" (port)
    );
}

uint16_t port_inw(uint16_t port)
{
    uint16_t res;
    asm (
        "in %%dx, %%al":
        "=a" (res):
        "d" (port)
    );
    return res;
}


void port_outw(uint16_t port, uint16_t data)
{
    __asm__(
    "out %%al, %%dx" ::
    "a" (data),
    "d" (port)
    );
}
