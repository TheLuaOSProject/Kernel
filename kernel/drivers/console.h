//
// Created by Frityet on 2021-09-10.
//

#ifndef LUAOS_KERNEL_DISPLAY
#define LUAOS_KERNEL_DISPLAY

#include "bootloader.h"

#include <types.h>
#include <lib/string.h>

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

extern const cstr_t ANSI_ESCAPE_CODES[];

static void kprint(cstr_t msg);
static void kprintln(cstr_t msg);

static void kprintf(cstr_t fmt, ...);
static void kprintfln(cstr_t fmt, ...);

static void kprints(cstr_t msg, enum ansi_escape_codes styles[]);
static void kprintsln(cstr_t msg, enum ansi_escape_codes styles[]);

static void kset_style(const enum ansi_escape_codes code, bool reset);
static void kset_styles(const enum ansi_escape_codes codes[], bool reset);

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
    
    /**
     * Prints with the specified style(s)
     */
    void    (*prints)(cstr_t msg, enum ansi_escape_codes styles[]);
    
    /**
     * Prints a line with the specified style(s)
     */
     void   (*printsln)(cstr_t msg, enum ansi_escape_codes styles[]);

    /**
    * Sets the console style
    */
    void    (*set_style)(enum ansi_escape_codes style, bool reset);
     
    /**
    * Sets the console styles
    */
    void    (*set_styles)(enum ansi_escape_codes styles[], bool reset);
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
