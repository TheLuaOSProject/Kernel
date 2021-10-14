//
// Created by Frityet on 2021-09-12.
//

#ifndef LUAOS_BOOTLOADER
#define LUAOS_BOOTLOADER
#include <stdint.h>
#include <stddef.h>
#include <stivale2.h>

#define STACK_SIZE          2 << 13

// We need to tell the stivale bootloader where we want our stack to be.
// We are going to alloc our stack as an uninitialised array in .bss.
static uint8_t stack[STACK_SIZE];

/**
 * Gets the specified Stivale2 tag
 * @param stivale2_struct Stivale2 struct given in the kernel entrypoint
 * @param id ID of the tag to get
 * @return Value of the tag
 */
void *get_stivale_tag(struct stivale2_struct *stivale2_struct, uint64_t id);


#endif //LUAOS_BOOTLOADER
