///
/// @author Amrit Bhogal on 2023-03-14
/// @brief 
/// @version 1.0.0
///
#pragma once

#include <stdint.h>

#define APIC_BASE_MSR 0x1B

static uint64_t read_msr(uint32_t msr)
{
    uint32_t low, high;
    asm("rdmsr" : "=a"(low), "=d"(high) : "c"(msr));
    return ((uint64_t)high << 32) | low;
}

static void write_msr(uint32_t msr, uint64_t value)
{
    uint32_t low = value & 0xFFFFFFFF;
    uint32_t high = value >> 32;
    asm("wrmsr" : : "a"(low), "d"(high), "c"(msr));
}
