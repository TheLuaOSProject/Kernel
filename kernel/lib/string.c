//
// Created by Frityet on 2021-09-08.
//

#include <stdarg.h>

#include <common.h>

#include "string.h"

size_t strlen(const string str)
{
    size_t len = 0;

    char ch = str[0];
    while (ch != '\0')
    {
        ++len;
        ch = str[len];
    }
    
    return len;
}

string strcat(string str1, string str2)
{
    static char buffer[1024]; //fuck you, I am too tired to try and make this safe

    size_t  str1_len    = strlen(str1),
            str2_len    = strlen(str2);

    for (int i = 0; i < str1_len; ++i) {
        buffer[i] = str1[i];
    }

    for (int i = 0; i < str2_len; ++i) {
        buffer[str1_len + i] = str2[i];
    }
    
    return buffer;
}

__attribute__((unused)) string strcatv(string str1, ...)
{
    va_list argv;
    size_t  argc = VA_ARGS_COUNT(...),
            strc[argc];
    string strv[argc];
    
    va_start(argv, str1);
    
    for (int i = 0; i < argc; ++i) {
        strv[i] = va_arg(argv, string);
        strc[i] = strlen(strv[i]);
    }

    va_end(argv);
}

void strcpy(string dest, const string src)
{
    int i = 0;
    do {
        dest[i] = src[i];
        ++i;
    } while (src[i] != '\0');

    dest[i] = src[i]; //Null termination
}

void reverse(string str)
{
    int c, i, j;
    for (i = 0, j = strlen(str)-1; i < j; i++, j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void append(string str, char character)
{
    size_t len = strlen(str);
    str[len] = character;
    str[len + 1] = '\0';
}

string strnum(int64_t num, enum base base)
{
    static char buffer[32];
    uint8_t i, sign;

    if (base == BASE_10) {
        if ((sign = num) < 0) num = -num;
        i = 0;
        do {
            buffer[i++] = num % 10 + '0';
        } while ((num /= 10) > 0);

        if (sign < 0) buffer[i++] = '-';
        buffer[i] = '\0';

        reverse(buffer);
    }

    if (base == BASE_16) {
        append(buffer, '0');
        append(buffer, 'x');
        char zeros = 0;

        int32_t tmp;
        for (i = 28; i > 0; i -= 4) {
            tmp = (num >> i) & 0xF;
            if (tmp == 0 && zeros == 0) continue;
            zeros = 1;
            if (tmp > 0xA) append(buffer, tmp - 0xA + 'a');
            else append(buffer, tmp + '0');
        }

        tmp = num & 0xF;
        if (tmp >= 0xA) append(buffer, tmp - 0xA + 'a');
        else append(buffer, tmp + '0');
    }

    return buffer;
}
