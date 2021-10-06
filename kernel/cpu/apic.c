//
// Created by Frityet on 2021-10-06.
//

#include "apic.h"

struct apic apic;

static void enable_apic(void)
{
}

static uint32_t read_apic_register(enum apic_register offset)
{
    return 0;
}

static void write_apic_register(enum apic_register offset, uint32_t value)
{
    
}

static void send_apic_eoi()
{

}

static void send_ipi(uint8_t destination, uint8_t vector, uint32_t type)
{

}

void initialise_apic(void)
{
    if (apic.initialised) return;

    apic.enable = &enable_apic;
    apic.read_register = &read_apic_register;
    apic.write_register = &write_apic_register;
    apic.send_eoi = &send_apic_eoi;
    apic.send_ipi = &send_ipi;
    
    apic.initialised = true;
}

