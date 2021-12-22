/**
 * @file    console.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Interface with the VGA console output
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */

#ifndef LUAOS_KERNEL_DISPLAY
#define LUAOS_KERNEL_DISPLAY

#include <types.h>
#include <common.h>

#include "screen.h"

enum ansi_escape_codes
{
    ESCAPE              = 0,
    
    CURSOR_HOME         = 1,
    
    CLEAR_SCREEN        = 2,
    CLEAR_UNTIL_END     = 3,
    CLEAR_TO_START      = 4,
    CLEAR_ALL           = 5,
    CLEAR_LINE          = 6,
    CLEAR_TO_ENDL       = 7,
    CLEAR_TO_STARTLN    = 8,
    CLEAR_LINE_ALL      = 9,
    
    RESET_STYLES        = 10,
    STYLE_BOLD          = 11,
    STYLE_DIM           = 12,
    STYLE_ITALIC        = 13,
    STYLE_UNDERLINE     = 14,
    STYLE_BLINKING      = 15,
    STYLE_REVERSE       = 16,
    STYLE_HIDDEN        = 17,
    STYLE_STRIKETHROUGH = 18
};

extern const string_t ANSI_ESCAPE_CODES[];

#define CONSOLE_COLOURS_RESET               "\x1b[0m"

#define CONSOLE_COLOURS_FOREGROUND_BLACK    "\x1b[30m"
#define CONSOLE_COLOURS_FOREGROUND_RED      "\x1b[31m"
#define CONSOLE_COLOURS_FOREGROUND_GREEN    "\x1b[32m"
#define CONSOLE_COLOURS_FOREGROUND_YELLOW   "\x1b[33m"
#define CONSOLE_COLOURS_FOREGROUND_BLUE     "\x1b[34m"
#define CONSOLE_COLOURS_FOREGROUND_MAGENTA  "\x1b[35m"
#define CONSOLE_COLOURS_FOREGROUND_CYAN     "\x1b[36m"
#define CONSOLE_COLOURS_FOREGROUND_WHITE    "\x1b[37m"
#define CONSOLE_COLOURS_FOREGROUND_DEFAULT  "\x1b[39m"

#define CONSOLE_COLOURS_BACKGROUND_BLACK    "\x1b[40m"
#define CONSOLE_COLOURS_BACKGROUND_RED      "\x1b[41m"
#define CONSOLE_COLOURS_BACKGROUND_GREEN    "\x1b[42m"
#define CONSOLE_COLOURS_BACKGROUND_YELLOW   "\x1b[43m"
#define CONSOLE_COLOURS_BACKGROUND_BLUE     "\x1b[44m"
#define CONSOLE_COLOURS_BACKGROUND_MAGENTA  "\x1b[45m"
#define CONSOLE_COLOURS_BACKGROUND_CYAN     "\x1b[46m"
#define CONSOLE_COLOURS_BACKGROUND_WHITE    "\x1b[47m"
#define CONSOLE_COLOURS_BACKGROUND_DEFAULT  "\x1b[49m"

void console_println(string_t msg);
void console_print(string_t msg);
void console_clear(void);
void console_printf(string_t fmt, ...);
void console_printfln(string_t fmt, ...);
void console_prints(string_t msg, enum ansi_escape_codes styles[]);
void console_printsln(string_t msg, enum ansi_escape_codes styles[]);
void console_setstyle(enum ansi_escape_codes style);
void console_setstyles(const enum ansi_escape_codes styles[]);


/**
 * Sets up a kernel console will correct callbacks
 * @param bootloader Stivale2 struct passed in the kernel entry point
 * @return The setup wrapper
 */
bool initialise_console(struct stivale2_struct *bootloader);

#endif //LUAOS_KERNEL_DISPLAY
