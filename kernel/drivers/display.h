//
// Created by Frityet on 2021-09-10.
//

#ifndef LUAOS_KERNEL_DISPLAY
#define LUAOS_KERNEL_DISPLAY

#include "stivale.h"

#include <types.h>
#include <lib/string.h>

static void kprint(cstr_t msg);
static void kprintln(cstr_t msg);

static void clear(void);

/**
 * Wrapper over the Stivale2 console interface 
 */
struct kernel_console {
    void    (*println)(cstr_t msg);
    void    (*print)(cstr_t msg);
    
    void    (*clear)(void);
};


static void (*stivale_print)(const char *string, size_t length);

/**
 * Sets up a kernel console will correct callbacks
 * @param bootloader Stivale2 struct passed in the kernel entry point
 * @return The setup wrapper
 */
struct kernel_console setup_console(struct stivale2_struct *bootloader);

static struct stivale2_struct_tag_terminal *terminal_tag;

#endif //LUAOS_KERNEL_DISPLAY
