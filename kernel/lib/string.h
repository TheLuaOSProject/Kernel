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
 * Converts an hexadecimal number to a string
 * @param hex Hexadecimal value
 * @param output Output of the converison
 */
__attribute__((unused)) void strhex(uint64_t hex, string_t output);


#endif //LUAOS_STRING
