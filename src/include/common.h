///
///@file common.h
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

#pragma once

#define ATTRIBUTE(...) __attribute__((__VA_ARGS__))

#define force_inline ATTRIBUTE(always_inline) inline
#define pure ATTRIBUTE(pure)
