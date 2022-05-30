///
///@file string.h
///@author frityet
///@version 1.0.0
///


#pragma once

#include "types.h"
#include "common.h"

typedef struct String {
    uint64      length;
    const char  *buffer;
} string;

uint64 string_length(const char *str);

static inline string str(const char *str)
{
    uint64 i = string_length(str);
    return (string) {
        .length = i,
        .buffer = str
    };
}

static inline string strl(const char *str, uint32 len)
{
    return (string) {
        .length = len,
        .buffer = str
    };
}

string string_concat(string s1, string s2);
