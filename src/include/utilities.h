//
// Created by Frityet on 2022-02-08.
//

#ifndef LUAOS_UTILITIES_
#define LUAOS_UTILITIES_

#include "common.h"

#include <stivale2.h>

ATTRIBUTE(noreturn)
extern void CRASH();

ATTRIBUTE(noreturn)
extern void HALT();

void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id);

#endif //LUAOS_UTILITIES_
