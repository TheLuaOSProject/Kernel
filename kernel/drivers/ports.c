#include "ports.h"

u8char_t port_in(u16short_t port)
{
    u8char_t res;
    
    __asm__(
        "in %%dx, %%al" 
        : "=a" (res) 
        : "d" (port)
    );
    
    return res;
}

void port_out(u16short_t port, u8char_t data)
{
    __asm__(
        "out %%al, %%dx" :: 
        "a" (data), 
        "d" (port)
    );
}

u16short_t wport_in(u16short_t port)
{
    u16short_t res;
    __asm__(
        "in %%dx, %%al" 
        : "=a" (res) 
        : "d" (port)
    );
    return res;
}


void wport_out(u16short_t port, u16short_t data)
{
    __asm__(
        "out %%al, %%dx" ::
        "a" (data),
        "d" (port)
    );
}