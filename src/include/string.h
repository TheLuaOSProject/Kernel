///
///@file string.h
///@author frityet
///@version 1.0.0
///


#pragma once

#include "types.h"
#include "common.h"

typedef struct String {
    const uint32    max;
    uint32          length;
    char            *buffer;
} string;

uint32 string_length(const char *str);

static inline string str(const char *str)
{
    uint32 i = string_length(str);
    return (string) {
        .length = i,
        .max = i,
        .buffer = (char *)str
    };
}

static inline string strl(const char *str, uint32 len)
{
    return (string) {
        .length = len,
        .max    = len,
        .buffer = (char *)str
    };
}

void string_concat(string dst, const char *src, uint32 len);
void string_copy(string dst, const char *src, uint32 len);
