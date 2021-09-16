//
// Created by Frityet on 2021-09-16.
//

#include "utilities.h"


void copy_memory(const  int8_t      *src,
                        int8_t      *dest, 
                        int         byte_count)
{
    for (int i = 0; i < byte_count; ++i) {
        *(dest + i) = *(src + i);
    }
}
//K&R ftw 
void strint(int num, char *output)
{
    int i = 0, sign = num;
    if (sign < 0) num = -num;
    
    do {
        output[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0) output[i++] = '-';
    output[i] = '\0';
}
