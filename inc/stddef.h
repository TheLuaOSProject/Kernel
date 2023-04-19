#pragma once

#include <stdint.h>

typedef unsigned long size_t;
typedef long ssize_t;

#define nullable _Nullable
#define nonnull _Nonnull

#define NULL ((void *nullable)0)
#define nullptr ((void *nullable)0)

#define offsetof(s, m) __builtin_offsetof(s, m)
