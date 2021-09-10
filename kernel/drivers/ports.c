#include "ports.h"

uchar8_t port_in(ushort16_t port)
{
    uchar8_t res;
    
    __asm__(
        "in %%dx, %%al" 
        : "=a" (res) 
        : "d" (port)
    );
    
    return res;
}

void port_out(ushort16_t port, uchar8_t data)
{
    __asm__(
        "out %%al, %%dx" :: 
        "a" (data), 
        "d" (port)
    );
}

ushort16_t wport_in(ushort16_t port)
{
    ushort16_t res;
    __asm__(
        "in %%dx, %%al" 
        : "=a" (res) 
        : "d" (port)
    );
    return res;
}


void wport_out(ushort16_t port, ushort16_t data)
{
    __asm__(
        "out %%al, %%dx" ::
        "a" (data),
        "d" (port)
    );
}