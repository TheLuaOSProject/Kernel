//
// Created by Frityet on 2021-10-03.
//

#include "keyboard.h"

#include "console.h"
#include "logger.h"
#include "types.h"

const char NORMAL_KEYS[] = {
        '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-',
        '=', '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',
        ']', '\0', '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
        '`', '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
        '\0', '\0', '\0', ' '
};

const char CAPITAL_KEYS[] = {
        '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-',
        '=', '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[',
        ']', '\0', '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'',
        '`', '\0', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/',
        '\0', '\0', '\0', ' '
};

const char SHIFT_KEYS[] = {
        '\0', '\0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
        '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
        '\0', '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
        '\0', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?'
};

const char SHIFT_CAPITAL_KEYS[] = {
        '\0', '\0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
        '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}',
        '\0', '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ':', '"', '~',
        '\0', '|', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '<', '>', '?'
};

static struct {
    bool shift;
    bool caps;
} kb_state = {
        .shift  = false,
        .caps   = false
};

extern void ASM_KEYBOARD();

void initialise_keyboard(void)
{
    logger.writeln("KEYBOARD INIT");
    register_interrupt_handler(0x21, 
                               (uint64_t)&ASM_KEYBOARD,
                               0x8E,
                               0);
    logger.writeln("DONE");
}

void keyboard_i(__attribute__((unused)) struct interrupt_frame *iframe)
{
    logger.writeln("Key pressed!");
    uint8_t key = port_in(0x60);
    logger.writefln("Key: %", NORMAL_KEYS[key]);

    //0x59 = max scan code
    if (key >= 0x59) {
        uint8_t released_key = key - 0x80;

        switch (released_key) {
            case LEFT_SHIFT:
            case RIGHT_SHIFT:
                kb_state.shift = false;
                break;
            default:
                break;
        }
    }

    switch (key) {
        case LEFT_SHIFT:
        case RIGHT_SHIFT:
            kb_state.shift = true;
            return;
        case CAPS_LOCK:
            kb_state.caps = true;
            return;
        default:
            break;
    }
    
    __attribute__((unused))
    char buffer;

    if (kb_state.shift && kb_state.caps) {
        buffer = SHIFT_CAPITAL_KEYS[key];
    } else if (kb_state.shift) {
        buffer = SHIFT_KEYS[key];
    } else if (kb_state.caps) {
        buffer = CAPITAL_KEYS[key];
    } else {
        buffer = NORMAL_KEYS[key];
    }
    
    // console.print(buffer);
}
