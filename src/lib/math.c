/**
 * Copyright (C) 2023 Louis Dupraz
 *
 * This file is part of LuaOS.
 *
 * LuaOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LuaOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
 */

// These are macros defined in math.h.
// They are not used yet but will be used in the future for error handling.
// They may also be used in other files.

#define NAN 0.0 / 0.0
#define HUGE_VAL 1e10000
#define HUGE_VALF 1e10000f
#define INFINITY INF

#include <float.h>

typedef union {
    float f;
    char b[4];
} float_bytes;

typedef union {
    double d;
    char b[8];
} double_bytes;

int isnan(double x)
{
    if (x != x)
        return (1);
    return (0);
}

int isinf(double x)
{
    return (x > DBL_MAX || x < -DBL_MAX);
}

double fabs(double x)
{
    double_bytes bytes = {x};
    bytes.b[7] &= 0x7F;
    return bytes.d;
}

float fabsf(float x)
{
    float_bytes bytes = {x};
    bytes.b[3] &= 0x7F;
    return bytes.f;
}
