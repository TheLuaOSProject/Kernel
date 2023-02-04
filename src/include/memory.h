#include "common.h"

ASSUME_NONNULL_BEGIN

static size_t memory_copy(void *dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return n;
}

static size_t memory_set(void *dest, int c, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        ((char *)dest)[i] = c;
    }
    return n;
}

static int memory_compare(const void *s1, const void *s2, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (((char *)s1)[i] < ((char *)s2)[i]) return -1;
        if (((char *)s1)[i] > ((char *)s2)[i]) return 1;
    }
    return 0;
}



ASSUME_NONNULL_END
