#include "ports.h"

uint8_t port_in(uint16_t port)
{
    uint8_t res;
    
    __asm__(
        "in %%dx, %%al" 
        : "=a" (res) 
        : "d" (port)
    );
    
    return res;
}

void port_out(uint16_t port, uint8_t data)
{
    __asm__(
        "out %%al, %%dx" :: 
        "a" (data), 
        "d" (port)
    );
}

uint16_t wport_in(uint16_t port)
{
    uint16_t res;
    __asm__(
        "in %%dx, %%al" 
        : "=a" (res) 
        : "d" (port)
    );
    return res;
}


void wport_out(uint16_t port, uint16_t data)
{
    __asm__(
        "out %%al, %%dx" ::
        "a" (data),
        "d" (port)
    );
}