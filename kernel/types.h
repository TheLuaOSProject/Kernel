#ifndef LUAOS_TYPES
#define LUAOS_TYPES

typedef unsigned int   u32_t;
typedef          int   s32_t;
typedef unsigned short u16_t;
typedef          short s16_t;
typedef unsigned char  u8_t;
typedef          char  s8_t;

typedef u32_t size_t;

#define LOW_16(address) (u16)((address) & 0xFFFF)
#define HIGH_16(address) (u16)(((address) >> 16) & 0xFFFF)

typedef char* string_t;

#endif