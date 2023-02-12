#include "memory.h"

void *memset(void *dest, int c, size_t n)
{
    memory_set(dest, c, n);
    return dest;
}
