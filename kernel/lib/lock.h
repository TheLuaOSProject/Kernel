//
// Created by Frityet on 2021-10-14.
//

#ifndef LUAOS_LOCK
#define LUAOS_LOCK

#include "types.h"

typedef struct {
    uint32_t reference_count_wait;
    uint32_t data;
} lock_t;



#endif //LUAOS_LOCK
