//
// Created by Frityet on 2021-09-10.
//

#include <stdarg.h>
#include <common.h>
#include <string.h>
#include "console.h"

static struct stivale2_struct_tag_terminal *terminal_tag;
static void (*stivale_print)(char *, size_t);

const string_t ANSI_ESCAPE_CODES[] = {
    "\x1b",     //ESCAPE
    
    /*Cursor*/
    "\x1b[H",   //CURSOR TO HOME POS
    
    /*Screen Clearing*/
    "\x1b[J",   //CLEAR SCREEN
    "\x1b[0J",  //CLEAR SCREEN UNTIL END
    "\x1b[1J",  //CLEAR SCREEN TO START
    "\x1b[2J",  //CLEAR ALL
    "\x1b[K",   //CLEAR LINE
    "\x1b[0K",  //CLEAR LINE FROM CURSOR TO ENDL
    "\x1b[1K",  //CLEAR LINE FROM CURSOR TO STARTL
    "\x1b[2K",  //CLEAR ENTIRE LINE
    
    /*Text Styling*/
    "\x1b[0m",  //RESET ALL STYLES
    "\x1b[1m",  //BOLD STYLE
    "\x1b[2m",  //DIM STYLE
    "\x1b[3m",  //ITALIC STYLE
    "\x1b[4m",  //UNDERLINE STYLE
    "\x1b[5m",  //BLINKING STYLE
    "\x1b[7m",  //REVERSE STYLE
    "\x1b[8m",  //HIDDEN STYLE
    "\x1b[9m",  //STRIKETHROUGH STYLE
};

bool initialise_console(struct stivale2_struct *bootloader)
{
    terminal_tag = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_TERMINAL_ID);


    stivale_print = (void *)terminal_tag->term_write;
    return true;
}

void console_printf(string_t fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    for (; *fmt != '\0'; fmt++) {
        if (*fmt == '%') {
            console_print(va_arg(arglist, string_t));
            continue;
        }
        stivale_print(fmt, 1);
    }

    va_end(arglist);
}

void console_printfln(string_t fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    for (; *fmt != '\0'; fmt++) {
        if(*fmt == '%') {
            console_print(va_arg(arglist, string_t));
            continue;
        }
        stivale_print(fmt, 1);
    }

    va_end(arglist);
    stivale_print("\n", 1);
}

void console_print(string_t msg)
{
    stivale_print(msg, strlen(msg));
}

void console_println(string_t msg)
{
    console_print(msg);
    stivale_print("\n", 1);
}

void console_prints(string_t msg, enum ansi_escape_codes styles[])
{
    console_setstyles(styles);
    console_print(msg);
}

void console_printsln(string_t msg, enum ansi_escape_codes styles[])
{
    console_prints(msg, styles);
    stivale_print("\n", 1);
}

void console_setstyle(const enum ansi_escape_codes code)
{
    console_print(ANSI_ESCAPE_CODES[code]);
}

void console_setstyles(UNUSED const enum ansi_escape_codes codes[])
{
    // if (reset) {
    //     console_print(ANSI_ESCAPE_CODES[RESET_STYLES]);
    // }
    
    // size_t codeslen = ARRAY_LENGTH(codes);

    // for (int i = 0; i < codeslen; ++i) {
    //     console_print(ANSI_ESCAPE_CODES[codes[i]]);
    // }
}

void console_clear(void)
{
    if (screen.initialised) {
        screen.cursor_position = POINT(0, 0);
    }
    console_print(ANSI_ESCAPE_CODES[CLEAR_ALL]);
}


