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
#include <float.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

int cisnan(double x)
{
    if (x != x)
        return (1);
    return (0);
}

int cisinf(double x)
{
    return (x > DBL_MAX || x < -DBL_MAX);
}

// Getting the remainder of x / y using euclidian division
double cfmod(double x, double y)
{
    if (cisnan(x) || cisnan(y) || y == 0 || cisinf(x))
        return NAN;
    if (x == 0)
        return 0;
    double remainder = x;
    while (remainder > y)
        remainder -= y;
    return remainder;
}

// log() implementation using minimax polynomial approximations
double custom_log(double x) {
    if (x <= 0)
        return -1;
    x = (x - 1) / (x + 1);
    double x_squared = x * x;
    const double ln_coeff[] = {
        -0.7212426472299298,
        0.8442039221872251,
        -1.1042056880970873,
        2.0008677725944513,
        -3.9997386299074163,
    };
    double result = 0;
    for (int i = 4; i >= 0; --i)
        result = result * x_squared + ln_coeff[i];
    return 2 * x * (1 + result);
}

// exp() implementation using Taylor series
double custom_exp(double x) {
    double result = 1;
    const int terms = 500000;
    double current_term = 1;
    for (int i = 1; i <= terms; ++i) {
        current_term *= x / i;
        result += current_term;
    }
    return result;
}


double cuspow(double x, double y)
{
    double result = 1;
    if (cfmod(y, 1.0) == 0.0) {
    }
    return 0.0;
}

int main(void)
{

    printf("-1 %f %f %s\n", exp(-1), custom_exp(-1), (exp(-1) == custom_exp(-1))
    ? "ok" : "ko");
    printf("0 %f %f %s\n", exp(0), custom_exp(0), (exp(0) == custom_exp(0))
        ? "ok" : "ko");
    printf("42 %f %f %s\n", exp(42), custom_exp(42), (exp(42) == custom_exp(42))
        ? "ok" : "ko");
    printf("-2.3 %f %f %s\n", exp(-2.3), custom_exp(-2.3), (exp(-2.3) ==
    custom_exp(2.3)) ? "ok" : "ko");
    printf("0.64 %f %f %s\n", exp(0.64), custom_exp(0.64), (exp(0.64) ==
    custom_exp(0.64)) ? "ok" : "ko");
    printf("69.42 %f %f %s\n", exp(69.42), custom_exp(69.42), (exp(69.42) ==
    custom_exp(69.42)) ? "ok" : "ko");
}
