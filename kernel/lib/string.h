//
// Created by Frityet on 2021-09-08.
//

#ifndef LUAOS_STRING
#define LUAOS_STRING

#include "types.h"

/**
 * Gets the length of a string
 * @param str string to measure
 * @return length of str
 */
size_t strlen(const cstring str);

/**
 * Converts an integer to a string
 * @param num Integer to convert
 * @param output Output from the conversion
 */
void strint(int num, cstring output);

/**
 * Concatinates 2 strings
 * @param str1 String 1
 * @param str2 String 2
 * @return The two strings, combined
 */
cstring strcat(cstring str1, cstring str2);

/**
 * Concatinates n strings
 * @param str1 String 1
 * @param ... n Strings
 * @return All of the strings, combined
 */
__attribute__((unused)) cstring strcatv(cstring str1, ...);

/**
 * Converts an hexadecimal number to a string
 * @param hex Hexadecimal value
 * @param output Output of the converison
 */
__attribute__((unused)) void strhex(uint64_t hex, cstring output);


void sprintf(cstring fmt, ...);

string_t str(cstring str);


#endif //LUAOS_STRING
