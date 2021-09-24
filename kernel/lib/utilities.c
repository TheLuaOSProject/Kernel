//
// Created by Frityet on 2021-09-16.
//

#include "utilities.h"

void set_memory(void        *pointer,
                uintmax_t   value,
                uintmax_t   bytes)
{
    for (int i = 0; i < bytes; ++i) {
        ((char *)pointer)[i] = value;
    }
}

void copy_memory(const  int8_t      *src,
                        int8_t      *dest, 
                        int         byte_count)
{
    for (int i = 0; i < byte_count; ++i) {
        *(dest + i) = *(src + i);
    }
}



