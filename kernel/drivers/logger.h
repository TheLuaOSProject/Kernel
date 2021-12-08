/**
 * @file    logger.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Utilities for writing to the QEMU console output
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */

#ifndef LUAOS_LOGGER
#define LUAOS_LOGGER

#include <common.h>


#define LOGGING_PORT    0x3F8

static void lwrite(string_t message);
static void lwritec(char character);
static void lwritef(string_t fmt, ...);
static void lwriteln(string_t message);
static void lwritecln(char character);
static void lwritefln(string_t fmt, ...);

extern struct logger {
    /**
     * Writes a message to the log
     * @param message message to write
     */
    void    (*write)(string_t message);

    /**
     * Writes a character to the log
     * @param character char to write
     */
    void    (*writec)(char character);
    void    (*writef)(string_t fmt, ...);
    void    (*writeln)(string_t message);
    void    (*writecln)(char character);
    void    (*writefln)(string_t fmt, ...);
} logger;

void initialise_logger(void);

#endif //LUAOS_LOGGER
