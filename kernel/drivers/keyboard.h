//
// Created by Frityet on 2021-10-03.
//

#ifndef LUAOS_KEYBOARD
#define LUAOS_KEYBOARD

#include <stdbool.h>

#include "ports.h"
#include "cpu/idt.h"

struct keyboard_state {
    bool shift;
    bool caps;
};

enum special_keys {
    LEFT_SHIFT = 0x2A,
    LEFT_CONTROL = 0x1D,
    CAPS_LOCK = 0x3A,
    ENTER = 0x1C,
    BACK = 0x0E,
    RIGHT_SHIFT = 0x36
};

extern const char NORMAL_KEYS[];
extern const char CAPITAL_KEYS[];
extern const char SHIFT_KEYS[];
extern const char SHIFT_CAPITAL_KEYS[];

void ikeyboard(struct interrupt_frame *frame);
void initialise_keyboard(void);

#endif //LUAOS_KEYBOARD
