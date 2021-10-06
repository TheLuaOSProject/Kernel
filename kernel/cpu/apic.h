//
// Created by Frityet on 2021-10-06.
//

#ifndef LUAOS_APIC
#define LUAOS_APIC

#include <common.h>

/* Copied from https://github.com/chocabloc/aeolos/blob/master/kernel/sys/apic/apic.h */

#define APIC_REGISTER_ID            0x20
#define APIC_REGISTER_VERSION       0x30
#define APIC_REGISTER_SPURIOUS_INT  0xF0
#define APIC_SPURIOUS_VECTOR_NUM    0xFF
#define APIC_FLAG_ENABLE            (1 << 8)

#define APIC_IPI_TYPE_INIT          0b101
#define APIC_IPI_TYPE_STARTUP       0b110

enum apic_register {
    LAPIC_ID        = 0x20,
    LAPIC_VERSION   = 0x30,
    APIC_EOI        = 0xB0,
    APIC_ICR_LOW    = 0x300,
    APIC_ICR_HIGH   = 0x310
};

static void enable_apic();
static uint32_t read_apic_register(enum apic_register offset);
static void write_apic_register(enum apic_register offset, uint32_t value);
static void send_apic_eoi();
static void send_ipi(uint8_t destination, uint8_t vector, uint32_t type);

extern struct apic {
    void        (*enable)();
    uint32_t    (*read_register)(uint16_t offset);
    void        (*write_register)(uint16_t offset, uint32_t value);
    void        (*send_eoi)();
    void        (*send_ipi)(uint8_t destination, uint8_t vector, uint32_t type);
    
    bool        initialised;
} apic;

void initialise_apic(void);

#endif //LUAOS_APIC
