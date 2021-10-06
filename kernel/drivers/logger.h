//
// Created by Frityet on 2021-10-05.
//

#ifndef LUAOS_LOGGER
#define LUAOS_LOGGER

#include <common.h>


#define LOGGING_PORT    0x3F8

#define LOG(str) \

static void lwrite(string_t message);
static void lwritec(char character);
static void lwritef(string_t message);
static void lwriteln(string_t message);
static void lwritecln(char character);
static void lwritefln(string_t message);

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
//    void    (*writef)(string_t message);
    void    (*writeln)(string_t message);
    void    (*writecln)(char character);
//    void    (*writefln)(string_t message);
} logger;

void initialise_logger(void);

#endif //LUAOS_LOGGER
