//
// Created by Frityet on 2021-09-08.
//

#include <stdarg.h>

#include "string.h"

size_t strlen(const string_t str)
{
    size_t len = 0;

    char ch = str[0];
    while (ch != '\0')
    {
        ++len;
        ch = str[len];
    }
    
    return len;
}

//K&R ftw 
void strint(int num, string_t output)
{
    int i = 0, sign = num;
    if (sign < 0) num = -num;

    do {
        output[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0) output[i++] = '-';
    output[i] = '\0';
}

__attribute__((unused)) void strhex(uint64_t hex, string_t output)
{
    uint64_t i = 0;
    
    if (hex < 0) hex = -hex;
    do {
        output[i++] = hex % 16 + '0';
    } while ((hex /= 10) > 0);

    if (hex < 0) output[i++] = '-';
     
    output[i] = '\0';
}
