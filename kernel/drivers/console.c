//
// Created by Frityet on 2021-09-10.
//

#include <stdarg.h>
#include <common.h>

#include "console.h"

static void kprintf(cstr_t fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    
    char *traverse;
    for (traverse = fmt; *traverse != '\0'; traverse++) {
        while(*traverse != '%')
        {
            stivale_print(traverse, 1);
            traverse++;
        }
        
        traverse++;
        kprint(va_arg(arglist, cstr_t));
    }

    va_end(arglist);
}

static void kprintfln(cstr_t fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    char *traverse;
    for (traverse = fmt; *traverse != '\0'; traverse++) {
        while(*traverse != '%')
        {
            stivale_print(traverse, 1);
            traverse++;
        }

        traverse++;
        kprint(va_arg(arglist, cstr_t));
    }

    va_end(arglist);
    stivale_print("\n", 1);
}

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
    kprint(ANSI_ESCAPE_CODES[CLEAR_ALL]);
}

struct kernel_console setup_console(struct stivale2_struct *bootloader)
{
    terminal_tag = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (terminal_tag == NULL) {
        HANG();
    }

    stivale_print = (void *)terminal_tag->term_write;

    struct kernel_console kconsole;

    kconsole.clear      = &clear;
    kconsole.print      = &kprint;
    kconsole.println    = &kprintln;
    kconsole.printf     = &kprintf;
    kconsole.printfln   = &kprintfln;

    return kconsole;
}