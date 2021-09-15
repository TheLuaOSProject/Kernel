//
// Created by Frityet on 2021-09-10.
//

#ifndef LUAOS_KERNEL_DISPLAY
#define LUAOS_KERNEL_DISPLAY

#include "bootloader.h"

#include <types.h>
#include <lib/string.h>

enum ANSI_ESCAPE_CODES
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

const cstr_t ANSI_ESCAPE_CODES[] = {
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

static void kprint(cstr_t msg);
static void kprintln(cstr_t msg);

static void kprintf(cstr_t fmt, ...);
static void kprintfln(cstr_t fmt, ...);

static void clear(void);

/**
 * Wrapper over the Stivale2 console interface 
 */
struct kernel_console {
    /**
     * Prints a line into the kernel console
     * @param msg Message to print
     */
    void    (*println)(cstr_t msg);
    
    /**
     * Prints into the kernel console
     * @param msg Message to print
     */
    void    (*print)(cstr_t msg);
    
    /**
     * Clears the kernel console
     */
    void    (*clear)(void);
    
    /**
     * Prints a string with the specified format
     */
    void    (*printf)(cstr_t fmt, ...);

    /**
    * Prints a line with the specified format
    */
    void    (*printfln)(cstr_t fmt, ...);
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
