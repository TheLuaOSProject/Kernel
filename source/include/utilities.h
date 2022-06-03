///
///@file utilities.h
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

#pragma once

#include "common.h"
#include "types.h"

ATTRIBUTE(noreturn)
extern void HALT(void),
            MEMORY_COPY(void *dst, void *src, uint64 nmemb),
            MEMORY_SET(void *dst, uint64 val, uint64 nmemb);

#define EVALUATE(x) x
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

