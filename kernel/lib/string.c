//
// Created by Frityet on 2021-09-08.
//

#include <stdarg.h>

#include "string.h"

size_t strlen(const cstr_t str)
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