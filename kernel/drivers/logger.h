//
// Created by Frityet on 2021-10-05.
//

#ifndef LUAOS_LOGGER
#define LUAOS_LOGGER

#include <common.h>


#define LOGGING_PORT    0x3F8

#define LOG(str) \

static void lwrite(string_t message);
static void lwritef(string_t message);
static void lwriteln(string_t message);
static void lwritefln(string_t message);

extern struct logger {
    void    (*write)(string_t message);
//    void    (*writef)(string_t message);
    void    (*writeln)(string_t message);
//    void    (*writefln)(string_t message);
} logger;

void initialise_logger(void);

#endif //LUAOS_LOGGER
