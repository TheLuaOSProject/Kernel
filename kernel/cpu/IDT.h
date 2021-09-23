//
// Created by Frityet on 2021-09-20.
//

#ifndef LUAOS_IDT
#define LUAOS_IDT

#include <common.h>

struct IDTentry {
    uint16_t    low_base;
    uint16_t    selector;
    uint8_t     interrupt_standard_table;
    uint8_t     flags;
    uint16_t    mid_base;
    uint16_t    high_base;
    uint32_t    reserved;
};

struct IDT {
    uint16_t    limit;
    int64_t     base;
};

struct registers {
    uint64_t    ds;
    uint64_t    rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;
    uint64_t    interrupt_number, error_code;
    uint64_t    rip, code_segment, eflags, useresp, ss;
};

#endif //LUAOS_IDT
