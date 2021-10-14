//
// Created by Frityet on 2021-10-14.
//

#ifndef LUAOS_LOCK
#define LUAOS_LOCK

#include "types.h"

typedef uint8_t lock_t;

inline void acquire_lock(lock_t *lock)
{
    while (__atomic_test_and_set(lock, __ATOMIC_ACQUIRE));
}

inline void release_lock(lock_t *lock)
{
    __atomic_clear(lock, __ATOMIC_RELEASE);
}

#endif //LUAOS_LOCK
