//
// Created by Frityet on 2022-01-31.
//

#ifndef LUAOS_COMMON_
#define LUAOS_COMMON_

#define HALT() while(1) 

#define ATTRIBUTE(...) __attribute__((__VA_ARGS__))

#ifdef bool
#undef bool
#endif
#ifdef true
#undef true
#endif
#ifdef false
#undef false
#endif
typedef enum bool {
    true = 1,
    false = 0,
    TRUE = 1,
    FALSE = 0
} bool;

#endif //LUAOS_COMMON_
