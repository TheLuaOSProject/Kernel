///
///@file qemu_log.h
///@author frityet
///@version 1.0.0
///


#pragma once

#include "logger.h"
#include "cpu/bootloader.h"

struct QemuLog {
    struct stivale2_struct_tag_mmio32_uart *transmitter;
};

static inline struct QemuLog QemuLog_initalise(const BootloaderInfo_t *bootloader)
{
    return (struct QemuLog) {
        .transmitter = bootloader_find_tag(bootloader, STIVALE2_STRUCT_TAG_MMIO32_UART)
    };
}

void QemuLog_print(const struct QemuLog *qemu, string msg);

#define QEMU_LOG(qemu, msg) QemuLog_print(qemu, LOG_FORMAT(msg))
