#ifndef LUAOS_TYPES
#define LUAOS_TYPES

#include <stdint.h>

#define LOW_16(address) (u16)((address) & 0xFFFF)
#define HIGH_16(address) (u16)(((address) >> 16) & 0xFFFF)

typedef uint32_t size_t;

typedef char* cstr_t;

#endif