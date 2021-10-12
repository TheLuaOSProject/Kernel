//
// Created by Frityet on 2021-10-05.
//

#ifndef LUAOS_LOGGER
#define LUAOS_LOGGER

#include <common.h>


#define LOGGING_PORT    0x3F8

#define LOG(str) \

static void lwrite(string message);
static void lwritec(char character);
static void lwritef(string fmt, ...);
static void lwriteln(string message);
static void lwritecln(char character);
static void lwritefln(string fmt, ...);

extern struct logger {
    /**
     * Writes a message to the log
     * @param message message to write
     */
    void    (*write)(string message);
    /**
     * Writes a character to the log
     * @param character char to write
     */
    void    (*writec)(char character);
    void    (*writef)(string fmt, ...);
    void    (*writeln)(string message);
    void    (*writecln)(char character);
    void    (*writefln)(string fmt, ...);
} logger;

void initialise_logger(void);

#endif //LUAOS_LOGGER