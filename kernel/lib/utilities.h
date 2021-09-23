//
// Created by Frityet on 2021-09-16.
//

#ifndef LUAOS_UTILITIES
#define LUAOS_UTILITIES
#include "types.h"

/**
 * Copies memory from a source to a destination
 * @param src Source memory
 * @param dest Destination of the memory
 * @param byte_count Number of bytes to copy
 */
void copy_memory(const  int8_t  *src, 
                        int8_t  *dest, 
                        int     byte_count);





#endif //LUAOS_UTILITIES
