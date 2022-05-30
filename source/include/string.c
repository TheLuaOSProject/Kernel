///
///@file string.c
///@author frityet
///@version 1.0.0
///

#include "string.h"

uint32 string_length(const char *str)
{
    uint32 i = 0;
    while (*str++) i++;
    return i;
}

void string_concat(string dst, const char *src, uint32 len)
{
    if (dst.length + len > dst.max) return;
    
    for (uint32 i = 0; i < len; i++, dst.length++)
        dst.buffer[dst.length + i] = src[i];
    
    dst.buffer[dst.length] = '\0';
}

void string_copy(string dst, const char *src, uint32 len)
{
    if (len > dst.max) return;
    
    dst.length = len;
    for (uint32 i = 0; i < len; i++)
        dst.buffer[i] = src[i];

    dst.buffer[dst.length] = '\0';
    
}


