//
// Created by Frityet on 2021-10-06.
//

#include "cpuid.h"

#include "drivers/logger.h"


static string vendor_name = NULL;
string get_vendor_name()
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

    BREAKPOINT();

    logger.writeln("Attempting to get CPU vendor name");
    logger.write("ECX register: ");
    for (int i = 0; i < 4; ++i) {
        logger.writefln("Index %: %", strnum(i, BASE_10), strnum(ecx[i], BASE_16));
        fullname[i] = ecx[i];
    }

    logger.write("EDX register: ");
    for (int i = 0; i < 4; ++i) {
        logger.writefln("Index %: %", strnum(i, BASE_10), strnum(edx[i], BASE_16));
        fullname[i + 4] = edx[i];
    }

    logger.write("EBX register: ");
    for (int i = 0; i < 4; ++i) {
        logger.writefln("Index %: %", strnum(i, BASE_10), strnum(ebx[i], BASE_16));
        fullname[i + 8] = ebx[i];
    }

    fullname[12] = '\0';

    logger.write("Final string: ");
    logger.writeln(fullname);

    strcpy(vendor_name, fullname);
    return vendor_name;
}
