//
// Created by Frityet on 2021-09-10.
//

#ifndef LUAOS_KERNEL_DISPLAY
#define LUAOS_KERNEL_DISPLAY

#include "types.h"
#include "lib/string.h"

#define VIDEO_MEMORY            0xb8000

#define MAX_ROWS                25
#define MAX_COLUMNS             80

#define SCREEN_CONTROL_REGISTER 0x3d
#define SCREEN_DATA_REGISTER    0x3d5;

enum colours {
    WHITE_ON_BLACK              = 0x0f,
    GREEN_ON_BLACK              = 0xA0,
    RED_ON_WHITE                = 0xf4
};


void clear_screen(void);
void kernel_print(string_t msg);
void kernel_print_at(string_t   msg, 
                     uint16_t   col, 
                     uint16_t   row);

#endif //LUAOS_KERNEL_DISPLAY
