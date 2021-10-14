#ifndef LUAOS_TYPES
#define LUAOS_TYPES

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * C String, expands to a char pointer
 */
typedef char* string;

typedef void* voidptr;

typedef void (*voidfunc_f)(void);

#endif