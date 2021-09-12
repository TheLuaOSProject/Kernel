#ifndef LUAOS_TYPES
#define LUAOS_TYPES
#include <stddef.h>
#include <stdint.h>

#define LOW_16(address) (u16)((address) & 0xFFFF)
#define HIGH_16(address) (u16)(((address) >> 16) & 0xFFFF)

typedef char* cstr_t;

#endif