//
// Created by Frityet on 2021-10-05.
//

#include "logger.h"

#include "ports.h"

struct logger logger;

void initialise_logger(void)
{
    logger.write = &lwrite;
    logger.writec = &lwritec;
//    logger.writef = &lwritef;
    logger.writeln = &lwriteln;
    logger.writecln = &lwritecln;
//    logger.writefln = &lwritefln;
}

void lwrite(string_t message)
{
#ifdef QEMU
    for (int i = 0; i < strlen(message); ++i) {
        port_out(LOGGING_PORT, message[i]);
    }
#endif
}

void lwritec(char character)
{
#ifdef QEMU
    port_out(LOGGING_PORT, character);
#endif
}

void lwriteln(string_t message)
{
#ifdef QEMU
    lwrite(message);
    port_out(LOGGING_PORT, '\n');
#endif
}

void lwritecln(char character)
{
#ifdef QEMU
    lwritec(character);
    port_out(LOGGING_PORT, '\n');
#endif
}
