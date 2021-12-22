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

void logger_write(string_t message);
void logger_writec(char character);
void logger_writef(string_t fmt, ...);
void logger_writeln(string_t message);
void logger_writecln(char character);
void logger_writefln(string_t fmt, ...);

#endif //LUAOS_LOGGER
