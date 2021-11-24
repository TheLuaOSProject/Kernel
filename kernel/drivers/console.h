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

extern const string ANSI_ESCAPE_CODES[];

static void kprint(string msg);
static void kprintln(string msg);

static void kprintf(string fmt, ...);
static void kprintfln(string fmt, ...);

static void kprints(string msg, enum ansi_escape_codes styles[]);
static void kprintsln(string msg, enum ansi_escape_codes styles[]);

static void kset_style(enum ansi_escape_codes code, bool reset);
static void kset_styles(const enum ansi_escape_codes codes[], bool reset);

static void clear(void);

/**
 * Wrapper over the Stivale2 console interface 
 */
extern struct console {
    /**
     * Prints a line into the kernel console
     * @param msg Message to print
     */
    void    (*println)(string msg);
    
    /**
     * Prints into the kernel console
     * @param msg Message to print
     */
    void    (*print)(string msg);
    
    /**
     * Clears the kernel console
     */
    void    (*clear)(void);
    
    /**
     * Prints a string with the specified format
     */
    void    (*printf)(string fmt, ...);

    /**
    * Prints a line with the specified format
    */
    void    (*printfln)(string fmt, ...);
    
    /**
     * Prints with the specified style(s)
     */
    void    (*prints)(string msg, enum ansi_escape_codes styles[]);
    
    /**
     * Prints a line with the specified style(s)
     */
     void   (*printsln)(string msg, enum ansi_escape_codes styles[]);

    /**
    * Sets the console style
    */
    void    (*set_style)(enum ansi_escape_codes style, bool reset);
     
    /**
    * Sets the console styles
    */
    void    (*set_styles)(const enum ansi_escape_codes styles[], bool reset);

    point_t size;
    bool    initialised;
} console;


static void (*stivale_print)(const char *string, size_t length);

/**
 * Sets up a kernel console will correct callbacks
 * @param bootloader Stivale2 struct passed in the kernel entry point
 * @return The setup wrapper
 */
bool initialise_console(struct stivale2_struct *bootloader);

static struct stivale2_struct_tag_terminal *terminal_tag;

#endif //LUAOS_KERNEL_DISPLAY
