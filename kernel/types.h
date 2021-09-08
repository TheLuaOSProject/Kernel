#ifndef LUAOS_TYPES
#define LUAOS_TYPES

typedef unsigned int   u32int_t;
typedef          int   s32int_t;
typedef unsigned short u16short_t;
typedef          short s16short_t;
typedef unsigned char  u8char_t;
typedef          char  s8char_t;

typedef u32int_t size_t;

#define LOW_16(address) (u16)((address) & 0xFFFF)
#define HIGH_16(address) (u16)(((address) >> 16) & 0xFFFF)

typedef char* cstring_t;

#endif