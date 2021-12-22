//
// Created by Frityet on 2021-10-06.
//

#include "cpuid.h"
#include "drivers/logger.h"
#include <string.h>


static string_t vendor_name = NULL;
string_t get_vendor_name()
{
    if (vendor_name != NULL)
        return vendor_name;

    char    ebx[4],
            edx[4],
            ecx[4];

    static char fullname[13]; //Vendor name + null byte

    asm volatile (
            "CPUID\n"
            "MOV    %%EBX, %0\n"
            "MOV    %%EDX, %1\n"
            "MOV    %%ECX, %2\n"
            :"=rm" (ebx),
            "=rm" (edx),
            "=rm" (ecx)
    );

    logger_writeln("Attempting to get CPU vendor name");
    logger_write("ECX register: ");
    for (int i = 0; i < 4; ++i) {
        fullname[i] = ecx[i];
    }

    logger_write("EDX register: ");
    for (int i = 0; i < 4; ++i) {
        fullname[i + 4] = edx[i];
    }

    logger_write("EBX register: ");
    for (int i = 0; i < 4; ++i) {
        fullname[i + 8] = ebx[i];
    }

    fullname[12] = '\0';

    logger_write("Final string: ");
    logger_writeln(fullname);

    strcpy(vendor_name, fullname);
    return vendor_name;
}
