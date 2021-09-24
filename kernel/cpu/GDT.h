//
// Created by Frityet on 2021-09-23.
//

#ifndef LUAOS_GDT
#define LUAOS_GDT

#include <common.h>

struct gdt_descriptor {
    uint16_t    limit;
    uint64_t    offset;
} __attribute__((packed));

struct gdt_entry {
    uint16_t    limit0;
    uint16_t    base0;
    uint8_t     base1;
    uint8_t     access_byte;
    uint8_t     flags;
    uint8_t     base2;
} __attribute__((packed));


struct gdt {
    struct gdt_entry     null;
    struct gdt_entry     kernel_code;
    struct gdt_entry     kernel_data;
    
    struct gdt_entry     user_null;
    struct gdt_entry     user_code;
    struct gdt_entry     user_data;
} __attribute__((packed))
  __attribute((aligned(0x1000)));

extern const struct gdt global_descriptor_table;

extern void load_gdt(struct gdt_descriptor *descriptor);

#endif //LUAOS_GDT
