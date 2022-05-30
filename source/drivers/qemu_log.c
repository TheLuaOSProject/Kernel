///
///@file qemu_log.c
///@author frityet
///@version 1.0.0
///

#include "qemu_log.h"

#include "cpu/bootloader.h"

void QemuLog_print(const struct QemuLog *qemu, string msg)
{
    for (uint32 i = 0; i < msg.length; i++)
        *((uint32 *)qemu->transmitter->addr) = msg.buffer[i];
}
