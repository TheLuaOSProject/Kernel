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

//K&R ftw 
void strint(int num, string output)
{
    int i = 0, sign = num;
    if (sign < 0) num = -num;

    do {
        output[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0) output[i++] = '-';
    output[i] = '\0';
}

string strcat(string str1, string str2)
{
    size_t  str1_len    = strlen(str1),
            str2_len    = strlen(str2),
            catstr_len  = str1_len + str2_len;
    
    char catstr[catstr_len];

    for (int i = 0; i < str1_len; ++i) {
        catstr[i] = str1[i];
    }

    for (int i = 0; i < str2_len; ++i) {
        catstr[str1_len + i] = str2[i];
    }
    
    return catstr;
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

__attribute__((unused)) void strhex(uint64_t hex, string output)
{
    uint64_t i = 0;
    
    if (hex < 0) hex = -hex;
    do {
        output[i++] = hex % 16 + '0';
    } while ((hex /= 10) > 0);

    if (hex < 0) output[i++] = '-';
     
    output[i] = '\0';
}
