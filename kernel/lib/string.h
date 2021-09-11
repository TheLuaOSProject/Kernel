//
// Created by Frityet on 2021-09-08.
//

#ifndef LUAOS_STRING
#define LUAOS_STRING

#include "types.h"

typedef struct string {
    cstr_t  cstring;
    size_t  length;
    char    first_char;
    char    last_char;
} string_t;

struct string str(cstr_t str);

size_t strlen(cstr_t str);

#endif //LUAOS_STRING
