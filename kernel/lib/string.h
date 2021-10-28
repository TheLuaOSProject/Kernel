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
size_t strlen(string str);

/**
 * Concatinates 2 strings
 * @param str1 String 1
 * @param str2 String 2
 * @return The two strings, combined
 */
string strcat(string str1, string str2);

/**
 * Concatinates n strings
 * @param str1 String 1
 * @param ... n Strings
 * @return All of the strings, combined
 */
__attribute__((unused)) string strcatv(string str1, ...);

void strcpy(string dest, string src);

#define strnum(value) itoa(value, BASE_10) 
#define strhex(value) itoa(value, BASE_16)
string itoa(int64_t value, enum base base);


#endif //LUAOS_STRING
