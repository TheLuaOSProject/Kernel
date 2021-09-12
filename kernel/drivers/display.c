//
// Created by Frityet on 2021-09-10.
//

#include <common.h>

#include "display.h"

static void kprint(cstr_t msg)
{
    stivale_print(msg, strlen(msg));
}

static void kprintln(cstr_t msg)
{
    kprint(msg);
    stivale_print("\n", 1);
}

static void clear(void)
{
    
}

struct kernel_console setup_console(struct stivale2_struct *bootloader)
{
    terminal_tag = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (terminal_tag == NULL) {
        HANG();
    }
    
    stivale_print = (void *) terminal_tag->term_write;
    
    struct kernel_console kconsole;
    
    kconsole.clear      = &clear;
    kconsole.print      = &kprint;
    kconsole.println    = &kprintln;
    
    return kconsole;
}