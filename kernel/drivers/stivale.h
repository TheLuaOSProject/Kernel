//
// Created by Frityet on 2021-09-12.
//

#ifndef LUAOS_STIVALE
#define LUAOS_STIVALE
#include <stdint.h>
#include <stddef.h>
#include <stivale2.h>

/**
 * Gets the specified Stivale2 tag
 * @param stivale2_struct Stivale2 struct given in the kernel entrypoint
 * @param id ID of the tag to get
 * @return Value of the tag
 */
void *get_stivale_tag(struct stivale2_struct *stivale2_struct, uint64_t id);


#endif //LUAOS_STIVALE
