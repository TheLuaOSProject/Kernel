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
size_t strlen(const string_t str);

/**
 * Converts an integer to a string
 * @param num Integer to convert
 * @param output Output from the conversion
 */
void strint(int num, string_t output);

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

/**
 * Converts an hexadecimal number to a string
 * @param hex Hexadecimal value
 * @param output Output of the converison
 */
__attribute__((unused)) void strhex(uint64_t hex, string_t output);


void sprintf(string_t fmt, ...);


#endif //LUAOS_STRING
