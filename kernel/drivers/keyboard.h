/**
 * @file    keyboard.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Utilities for capturing keyboard input
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */

#ifndef LUAOS_KEYBOARD
#define LUAOS_KEYBOARD

#include <stdbool.h>

#include "ports.h"
#include "cpu/cpu.h"

enum special_keys {
    LEFT_SHIFT      = 0x2A,
    LEFT_CONTROL    = 0x1D,
    CAPS_LOCK       = 0x3A,
    ENTER           = 0x1C,
    BACK            = 0x0E,
    RIGHT_SHIFT     = 0x36
};

extern const char   NORMAL_KEYS[],
                    CAPITAL_KEYS[],
                    SHIFT_KEYS[],
                    SHIFT_CAPITAL_KEYS[];

void keyboard_i(struct interrupt_frame *iframe);
void initialise_keyboard(void);

extern void KEYBOARD_INPUT(void);

#endif //LUAOS_KEYBOARD
