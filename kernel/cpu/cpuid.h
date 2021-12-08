/**
 * @file    cpuid.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Wrapper over the CPUID instruction
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */

#ifndef LUAOS_CPUID
#define LUAOS_CPUID

#include <common.h>

enum cpuid_feature {
    CPUID_FEATURE_ECX_SSE3         = 1 << 0,
    CPUID_FEATURE_ECX_PCLMUL       = 1 << 1,
    CPUID_FEATURE_ECX_DTES64       = 1 << 2,
    CPUID_FEATURE_ECX_MONITOR      = 1 << 3,
    CPUID_FEATURE_ECX_DS_CPL       = 1 << 4,
    CPUID_FEATURE_ECX_VMX          = 1 << 5,
    CPUID_FEATURE_ECX_SMX          = 1 << 6,
    CPUID_FEATURE_ECX_EST          = 1 << 7,
    CPUID_FEATURE_ECX_TM2          = 1 << 8,
    CPUID_FEATURE_ECX_SSSE3        = 1 << 9,
    CPUID_FEATURE_ECX_CID          = 1 << 10,
    CPUID_FEATURE_ECX_FMA          = 1 << 12,
    CPUID_FEATURE_ECX_CX16         = 1 << 13,
    CPUID_FEATURE_ECX_ETPRD        = 1 << 14,
    CPUID_FEATURE_ECX_PDCM         = 1 << 15,
    CPUID_FEATURE_ECX_PCIDE        = 1 << 17,
    CPUID_FEATURE_ECX_DCA          = 1 << 18,
    CPUID_FEATURE_ECX_SSE4_1       = 1 << 19,
    CPUID_FEATURE_ECX_SSE4_2       = 1 << 20,
    CPUID_FEATURE_ECX_x2APIC       = 1 << 21,
    CPUID_FEATURE_ECX_MOVBE        = 1 << 22,
    CPUID_FEATURE_ECX_POPCNT       = 1 << 23,
    CPUID_FEATURE_ECX_AES          = 1 << 25,
    CPUID_FEATURE_ECX_XSAVE        = 1 << 26,
    CPUID_FEATURE_ECX_OSXSAVE      = 1 << 27,
    CPUID_FEATURE_ECX_AVX          = 1 << 28,

    CPUID_FEATURE_EDX_FPU          = 1 << 0,
    CPUID_FEATURE_EDX_VME          = 1 << 1,
    CPUID_FEATURE_EDX_DE           = 1 << 2,
    CPUID_FEATURE_EDX_PSE          = 1 << 3,
    CPUID_FEATURE_EDX_TSC          = 1 << 4,
    CPUID_FEATURE_EDX_MSR          = 1 << 5,
    CPUID_FEATURE_EDX_PAE          = 1 << 6,
    CPUID_FEATURE_EDX_MCE          = 1 << 7,
    CPUID_FEATURE_EDX_CX8          = 1 << 8,
    CPUID_FEATURE_EDX_APIC         = 1 << 9,
    CPUID_FEATURE_EDX_SEP          = 1 << 11,
    CPUID_FEATURE_EDX_MTRR         = 1 << 12,
    CPUID_FEATURE_EDX_PGE          = 1 << 13,
    CPUID_FEATURE_EDX_MCA          = 1 << 14,
    CPUID_FEATURE_EDX_CMOV         = 1 << 15,
    CPUID_FEATURE_EDX_PAT          = 1 << 16,
    CPUID_FEATURE_EDX_PSE36        = 1 << 17,
    CPUID_FEATURE_EDX_PSN          = 1 << 18,
    CPUID_FEATURE_EDX_CLF          = 1 << 19,
    CPUID_FEATURE_EDX_DTES         = 1 << 21,
    CPUID_FEATURE_EDX_ACPI         = 1 << 22,
    CPUID_FEATURE_EDX_MMX          = 1 << 23,
    CPUID_FEATURE_EDX_FXSR         = 1 << 24,
    CPUID_FEATURE_EDX_SSE          = 1 << 25,
    CPUID_FEATURE_EDX_SSE2         = 1 << 26,
    CPUID_FEATURE_EDX_SS           = 1 << 27,
    CPUID_FEATURE_EDX_HTT          = 1 << 28,
    CPUID_FEATURE_EDX_TM1          = 1 << 29,
    CPUID_FEATURE_EDX_IA64         = 1 << 30,
    CPUID_FEATURE_EDX_PBE          = 1 << 31
};

string_t get_vendor_name(void);

#endif //LUAOS_CPUID
