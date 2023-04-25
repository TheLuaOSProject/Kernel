/**
 * Copyright (C) 2023 pitust
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

#define NAN 0.0 / 0.0
# define HUGE_VAL 1e10000
# define HUGE_VALF 1e10000f
# define INF HUGE_VALF
#define INFINITY INF
#include <float.h>

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
    if (x < 0)
        return -x;
    return x;
}

float fabsf(float x)
{
    if (x < 0)
        return -x;
    return x;
}
