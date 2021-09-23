//
// Created by Frityet on 2021-09-20.
//

#include "GDT.h"

__attribute__((aligned(0x1000)))
const struct GDT global_descriptor_table = {
        .null = {
                .limit0         = 0,
                .base0          = 0,
                .base1          = 0,
                .access_byte    = 0x00,
                .limit1_flags   = 0x00,
                .base2          = 0
        },
        
        .kernel_code = {
                .limit0         = 0,
                .base0          = 0,
                .base1          = 0,
                .access_byte    = 0x9a,
                .limit1_flags   = 0xa0,
                .base2          = 0 
        },
        
        .kernel_data = {
                .limit0         = 0,
                .base0          = 0,
                .base1          = 0,
                .access_byte    = 0x92,
                .limit1_flags   = 0xa0,
                .base2          = 0
        },
        
        .user_null = {
                .limit0         = 0,
                .base0          = 0,
                .base1          = 0,
                .access_byte    = 0x00,
                .limit1_flags   = 0x00,
                .base2          = 0
        },

        .user_code = {
                .limit0         = 0,
                .base0          = 0,
                .base1          = 0,
                .access_byte    = 0x9a,
                .limit1_flags   = 0xa0,
                .base2          = 0
        },

        .user_data = {
                .limit0         = 0,
                .base0          = 0,
                .base1          = 0,
                .access_byte    = 0x92,
                .limit1_flags   = 0xa0,
                .base2          = 0
        },
};
