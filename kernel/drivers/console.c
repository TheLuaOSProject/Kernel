//
// Created by Frityet on 2021-09-10.
//

#include <stdarg.h>
#include <common.h>

#include "console.h"

struct console console;

const string ANSI_ESCAPE_CODES[] = {
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

    console.clear      = &clear;
    console.print      = &kprint;
    console.println    = &kprintln;
    console.printf     = &kprintf;
    console.printfln   = &kprintfln;
    console.prints     = &kprints;
    console.printsln   = &kprintsln;
    console.set_style  = &kset_style;
    console.set_styles = &kset_styles;

    console.size = POINT(terminal_tag->rows, terminal_tag->cols);

    console.initialised = true;

    return true;
}

static void kprintf(string fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    for (; *fmt != '\0'; fmt++) {
        if(*fmt == '%') {
            kprint(va_arg(arglist, string));
            continue;
        }
        stivale_print(fmt, 1);
    }

    va_end(arglist);
}

static void kprintfln(string fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    for (; *fmt != '\0'; fmt++) {
        if(*fmt == '%') {
            kprint(va_arg(arglist, string));
            continue;
        }
        stivale_print(fmt, 1);
    }

    va_end(arglist);
    stivale_print("\n", 1);
}

static void kprint(string msg)
{
    stivale_print(msg, strlen(msg));
}

static void kprintln(string msg)
{
    kprint(msg);
    stivale_print("\n", 1);
}

static void kprints(string msg, enum ansi_escape_codes styles[])
{
    kset_styles(styles, true);
    kprint(msg);
}

static void kprintsln(string msg, enum ansi_escape_codes styles[])
{
    kprints(msg, styles);
    stivale_print("\n", 1);
}

void kset_style(const enum ansi_escape_codes code, bool reset)
{
    if (reset) {
        kprint(ANSI_ESCAPE_CODES[RESET_STYLES]);
    }
    
    kprint(ANSI_ESCAPE_CODES[code]);
}

void kset_styles(const enum ansi_escape_codes codes[], bool reset)
{
    if (reset) {
        kprint(ANSI_ESCAPE_CODES[RESET_STYLES]);
    }
    
    size_t codeslen = ARRAY_LENGTH(codes);

    for (int i = 0; i < codeslen; ++i) {
        kprint(ANSI_ESCAPE_CODES[codes[i]]);
    }

}

static void clear(void)
{
    if (screen.initialised) {
        screen.cursor_position = POINT(0, 0);
    }
    kprint(ANSI_ESCAPE_CODES[CLEAR_ALL]);
}


