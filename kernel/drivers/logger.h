//
// Created by Frityet on 2021-10-05.
//

#ifndef LUAOS_LOGGER
#define LUAOS_LOGGER

#include <common.h>


#define LOGGING_PORT    0x3F8

#define LOG(str) \

static void lwrite(cstring message);
static void lwritec(char character);
static void lwritef(cstring message);
static void lwriteln(cstring message);
static void lwritecln(char character);
static void lwritefln(cstring message);

extern struct logger {
    /**
     * Writes a message to the log
     * @param message message to write
     */
    void    (*write)(cstring message);
    /**
     * Writes a character to the log
     * @param character char to write
     */
    void    (*writec)(char character);
//    void    (*writef)(string message);
    void    (*writeln)(cstring message);
    void    (*writecln)(char character);
//    void    (*writefln)(string message);
} logger;

void initialise_logger(void);

#endif //LUAOS_LOGGER
