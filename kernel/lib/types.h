#ifndef LUAOS_TYPES
#define LUAOS_TYPES

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * C String, expands to a char pointer
 */
typedef char *string_t;

typedef void *voidptr_t;

typedef void (*voidfunc_f)(void);

typedef uint8_t     byte_t;
typedef uint16_t    word_t;
typedef uint32_t    dword_t;
typedef uint64_t    qword_t;

#endif