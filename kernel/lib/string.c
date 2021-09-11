//
// Created by Frityet on 2021-09-08.
//

#include "string.h"

struct string str(cstr_t str)
{
    string_t string;
    
    string.cstring = str;
    string.length = strlen(str);
    string.first_char = str[0];
    string.last_char = str[string.length];
    
    return string;
}

size_t strlen(cstr_t str)
{
    size_t size = 0;
    char ch = str[0];
    
    while(ch != '\0') {
        ++size;
        ch = str[size];
    }
    
    return size;
}
