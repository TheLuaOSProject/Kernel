//
// Created by Frityet on 2021-09-23.
//

#ifndef LUAOS_GDT
#define LUAOS_GDT

#include <common.h>

struct GDTdescriptor {
    uint16_t    limit;
    uint64_t    offset;
} __attribute__((packed));

struct GDTentry {
    uint16_t    limit0;
    uint16_t    base0;
    uint8_t     base1;
    uint8_t     access_byte;
    uint8_t     flags;
    uint8_t     base2;
} __attribute__((packed));


struct GDT {
    struct GDTentry     null;
    struct GDTentry     kernel_code;
    struct GDTentry     kernel_data;
    
    struct GDTentry     user_null;
    struct GDTentry     user_code;
    struct GDTentry     user_data;
} __attribute__((packed))
  __attribute((aligned(0x1000)));

extern const struct GDT global_descriptor_table;

extern void load_gdt(struct GDTdescriptor *descriptor);

#endif //LUAOS_GDT
