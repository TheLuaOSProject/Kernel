//
// Created by Frityet on 2021-10-06.
//

#include "cpuid.h"

#include <cpuid.h>

#define cpuid(leaf, eax, ebx, ecx, edx)     __cpuid(leaf, eax, ebx, ecx, edx)
#define get_cpuid(leaf, eax, ebx, ecx, edx) __get_cpuid(leaf, eax, ebx, ecx, edx)

string get_vendor_name()
{

}

uint32_t get_cpu_model()
{
    uint32_t ebx, nil;
    cpuid(0, nil, ebx, nil, nil);
    return ebx;
}

bool check_apic(void)
{
    uint32_t eax, nil, edx;
    get_cpuid(1, &eax, &nil, &nil, &edx);
    return edx & CPUID_FEATURE_EDX_APIC;
}
