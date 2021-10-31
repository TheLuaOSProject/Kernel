//
// Created by Frityet on 2021-10-05.
//

#include "logger.h"

#include <stdarg.h>

struct logger logger;

void initialise_logger(void)
{
    logger.write    = &lwrite;
    logger.writec   = &lwritec;
    logger.writef   = &lwritef;
    logger.writeln  = &lwriteln;
    logger.writecln = &lwritecln;
    logger.writefln = &lwritefln;
}

void lwrite(string message)
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

void lwritef(string fmt, ...)
{
#ifdef QEMU
    va_list list;
    va_start(list, fmt);
    int i = 0;
    while(fmt[i] != '\0') {
        if (fmt[i] == '%') {
            lwrite(va_arg(list, string));
            goto end;
        }
        lwritec(fmt[i]);

        end:
        ++i;
    }

    va_end(list);
#endif
}

void lwritefln(string fmt, ...)
{
#ifdef QEMU
    va_list list;
    va_start(list, fmt);

    int i = 0;
    while(fmt[i] != '\0') {
        if (fmt[i] == '%')
            lwrite(va_arg(list, string));
        else
            lwritec(fmt[i]);

        ++i;
    }

    va_end(list);

    lwritec('\n');
#endif
}

void lwriteln(string message)
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
