//
// Created by Frityet on 2021-09-08.
//

#include <stdarg.h>

#include <common.h>

#include "string.h"

#define BUFFER_SIZE     128

static char buffer[BUFFER_SIZE];

static void clear_buffer(void)
{
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = 0;
    }
}

size_t strlen(const string_t str)
{
    size_t len = 0;
    char ch = str[0];
    while (ch != '\0') {
        ++len;
        ch = str[len];
    }
    return len;
}

string_t strcat(string_t str1, string_t str2)
{
    clear_buffer();

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

__attribute__((unused)) string_t strcatv(string_t str1, ...)
{
    va_list argv;
    size_t  argc = VA_ARGS_COUNT(...),
            strc[argc];
    string_t strv[argc];
    
    va_start(argv, str1);
    
    for (int i = 0; i < argc; ++i) {
        strv[i] = va_arg(argv, string_t);
        strc[i] = strlen(strv[i]);
    }

    va_end(argv);
}

void strcpy(string_t dest, const string_t src)
{
    int i = 0;
    do {
        dest[i] = src[i];
        ++i;
    } while (src[i] != '\0');

    dest[i] = src[i]; //Null termination
}

void reverse(string_t str)
{
    int c, i, j;
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void append(string_t str, char character)
{
    size_t len = strlen(str);
    str[len] = character;
    str[len + 1] = '\0';
}

string_t itoa(int64_t value, enum base base)
{
    clear_buffer();

    uint8_t signage = 0,
            i       = 0;

    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    if (value < 0 && base == BASE_10) {
        signage = 1;
        value = -value;
    }

    while(value) {
        int64_t digit = value % base;
        buffer[i++] = (digit > 9) ? (digit - 10) + 'a' : digit + '0';
        value = value / base;
    }

    if (signage)
        buffer[i++] = '-';

    buffer[i] = '\0';

    reverse(buffer);

    return buffer;
}
