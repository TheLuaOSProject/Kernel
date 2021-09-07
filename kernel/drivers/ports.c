#include "ports.h"

u8_t port_in(u16_t port)
{
    u8_t res;
    
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
}

void port_out(u16_t port, u8_t data)
{
}
