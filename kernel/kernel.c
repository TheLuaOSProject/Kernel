#include "kernel.h"

void kernel_start()
{
    port_out(0x3d4, 14);
    int pos = port_in(0x3d5);
    pos = pos << 8;

}
