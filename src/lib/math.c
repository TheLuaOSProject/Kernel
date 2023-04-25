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

double custom_abs(double x)
{
    if (x < 0)
        return -x;
    return x;
}

// Getting the remainder of x / y using euclidian division
double cfmod(double x, double y)
{
    if (cisnan(x) || cisnan(y))
        return NAN;
    if (y == 0 || cisinf(x)) {
        errno = EDOM;
        return NAN;
    }
    if (x == 0)
        return 0;
    int signx = 1, signy = 1;
    if (x < 0)
        signx = -1;
    if (y < 0)
        signy = -1;
    double remainder = custom_abs(x);
    double absy = custom_abs(y);
    while (remainder > absy)
        remainder -= absy;
    return remainder * signx;
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
    const int terms = 5000000;
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
    printf("Fmod testing\n");
    printf("NaN x : %f %f\n", fmod(NAN, 4), cfmod(NAN, 4));
    printf("NaN y : %f %f\n", fmod(7, NAN), cfmod(7, NAN));
    printf("y = 0 : %f %f\n", fmod(8, 0), cfmod(8, 0));
    printf("Inf x : %f %f\n", fmod(INF, 4), cfmod(INF, 4));
    printf("-2 / 4 : %f %f %s\n", fmod(-2, 4), cfmod(-2, 4), (fmod(-2, 4) ==
    cfmod(-2, 4)) ? "ok" : "ko");
    printf("-542.17 / -21.2 : %.15f %.15f %s\n", fmod(-542.17, -21.2), cfmod
    (-542.17, -21.2), (fmod(-542.17, -21.2) == cfmod(-542.17, -21.2)) ? "ok"
    : "ko");
    printf("8 / 3 : %f %f %s\n", fmod(8, 3), cfmod(8, 3), (fmod(8, 3) ==
    cfmod(8, 3)) ? "ok" : "ko");
    printf("634.53 / 45.4: %.15f %.15f %s\n", fmod(634.53, 45.4), cfmod(634.53,
        45.4), (fmod(634.53, 45.4) == cfmod(634.53, 45.40)) ? "ok" : "ko");
    printf("\n\nExp testing\n");
    printf("-1 %.20f %.20f %s\n\n", exp(-1), custom_exp(-1), (exp(-1) ==
    custom_exp(-1)) ? "ok" : "ko");
    printf("0 %f %f %s\n\n", exp(0), custom_exp(0), (exp(0) == custom_exp(0))
        ? "ok" : "ko");
    printf("42 %f %f %s\n\n", exp(42), custom_exp(42), (exp(42) == custom_exp
    (42))
        ? "ok" : "ko");
    printf("-2.3 %.20f %.20f %s\n\n", exp(-2.3), custom_exp(-2.3), (exp(-2.3) ==
    custom_exp(2.3)) ? "ok" : "ko");
    printf("0.64 %.20f %.20f %s\n\n", exp(0.64), custom_exp(0.64), (exp(0.64) ==
    custom_exp(0.64)) ? "ok" : "ko");
    printf("69.42 %f %f %s\n\n", exp(69.42), custom_exp(69.42), (exp(69.42) ==
    custom_exp(69.42)) ? "ok" : "ko");
}
