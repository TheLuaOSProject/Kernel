#ifndef LUAOS_TYPES
#define LUAOS_TYPES

typedef unsigned int   uint32_t;
typedef          int   int32_t;
typedef unsigned short ushort16_t;
typedef          short short16_t;
typedef unsigned char  uchar8_t;
typedef          char  char8_t;

typedef uint32_t size_t;

#define LOW_16(address) (u16)((address) & 0xFFFF)
#define HIGH_16(address) (u16)(((address) >> 16) & 0xFFFF)

typedef char* cstr_t;

#endif