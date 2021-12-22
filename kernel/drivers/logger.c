//
// Created by Frityet on 2021-10-05.
//

#include "logger.h"

#include <stdarg.h>
#include <string.h>
#include <drivers.h>

void logger_write(string_t message)
{
#ifdef QEMU
    for (size_t i = 0; i < strlen(message); ++i) {
        port_out(LOGGING_PORT, message[i]);
    }
#endif
}

void logger_writec(char character)
{
#ifdef QEMU
    port_out(LOGGING_PORT, character);
#endif
}

void logger_writef(string_t fmt, ...)
{
#ifdef QEMU
    va_list list;
    va_start(list, fmt);
    int i = 0;
    while (fmt[i] != '\0') {
        if (fmt[i] == '%') {
            logger_write(va_arg(list, string_t));

            goto end;
        }
        logger_writec(fmt[i]);

        end:
        ++i;
    }

    va_end(list);
#endif
}

void logger_writefln(string_t fmt, ...)
{
#ifdef QEMU
    va_list list;
    va_start(list, fmt);

    int i = 0;
    while(fmt[i] != '\0') {
        if (fmt[i] == '%')
            logger_write(va_arg(list, string_t));
        else
            logger_writec(fmt[i]);

        ++i;
    }

    va_end(list);

    logger_writec('\n');
#endif
}

void logger_writeln(string_t message)
{
#ifdef QEMU
    logger_write(message);
    port_out(LOGGING_PORT, '\n');
#endif
}

void logger_writecln(char character)
{
#ifdef QEMU
    logger_writec(character);
    port_out(LOGGING_PORT, '\n');
#endif
}
