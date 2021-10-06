#ifndef LUAOS_TYPES
#define LUAOS_TYPES

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * C String, expands to a char pointer
 */
typedef char* cstring;

typedef struct string {
    size_t  length;
    cstring buffer;
} string_t;



typedef void (*voidfunc_f)(void);

#endif