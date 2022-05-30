///
///@file string.c
///@author frityet
///@version 1.0.0
///

#include "string.h"

uint64 string_length(const char *str)
{
    uint64 i = 0;
    while (*str++) i++;
    return i;
}

string string_concat(string s1, string s2)
{
    static char strbuf[1024];
    string s = {
        .buffer = strbuf,
        .length = s1.length + s2.length
    };
    
    uint64 i;
    for (i = 0; i < s1.length; i++)
        strbuf[i] = s1.buffer[i];
    for (uint64 j = 0; j < s2.length; j++)
        strbuf[i + j] = s2.buffer[j];
    
    strbuf[s.length] = '\0';
    
    return s;
}
