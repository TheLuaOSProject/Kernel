#pragma once

#define bool _Bool
#define true 1
#define false 0

typedef unsigned long size_t;
typedef long ssize_t;

#define NULL (_Pragma("GCC warning \"ixOS code style: 'Use `null` not `NULL`\"")(void*) 0)
#define null ((void*)0)
