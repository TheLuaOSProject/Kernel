//
// Created by Frityet on 2021-09-08.
//

#ifndef LUAOS_STRING
#define LUAOS_STRING

#include "types.h"

enum base {
    BASE_10 = 10,
    BASE_16 = 16
};

/**
 * Gets the length of a string
 * @param str string to measure
 * @return length of str
 */
size_t strlen(string_t str);

/**
 * Concatinates 2 strings
 * @param str1 String 1
 * @param str2 String 2
 * @return The two strings, combined
 */
string_t strcat(string_t str1, string_t str2);

/**
 * Concatinates n strings
 * @param str1 String 1
 * @param ... n Strings
 * @return All of the strings, combined
 */
__attribute__((unused)) string_t strcatv(string_t str1, ...);

void strcpy(string_t dest, string_t src);

#define STRDEC(value) itoa(value, BASE_10) 
#define STRHEX(value) itoa(value, BASE_16)
string_t itoa(int64_t value, enum base base);


#endif //LUAOS_STRING
