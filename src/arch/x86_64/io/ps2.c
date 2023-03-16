#include "luck/io/log.h"
#include "stdint.h"
#include "stdbool.h"
#include "luck/arch/x86_64/io/ps2.h"
#include "luck/arch/x86_64/io/port.h"

static const uint8_t key_codes[] = {
    0, /*todo:escape*/ 0,
    0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x1b,
    0x28, 0x29, 0x34, 0,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
    0x2a, 0x2b, 0x33, 0,
    0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2,
    0x25, 0x30, 0x32, 0x53, 0x2c,
    0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9,
    0x31, 0x2f, 0x2e,
    0x53, // technically rshift is 0x54, but the bootrom does not recognize it correctly.
    0, 0, 0x26,
};
static char c1[] = "\e 1234567890-=\b\tqwertyuiop[]\n\0asdfghjkl;'`\0\\zxcvbnm,./\0\0\0 ";
static char c2[] = "\e !@#$%^&*()_+\b\tQWERTYUIOP{}\n\0ASDFGHJKL:\"~\0|ZXCVBNM<>?\0\0\0 ";
extern bool kbd_state[0x100];
extern bool kbd_enable_lsic;
static bool is_extended = false;
static bool shift = false;
char ps2_getc(void) {
    while (true) {
        if (port_in_byte(0x64) & 1) {
            uint8_t byte = port_in_byte(0x60);
            if (byte == 0xe0) {
                is_extended = true;
                continue;
            }
            bool pressed = byte & 0x80 ? false : true;
            const char* mode = byte & 0x80 ? "release" : "press";
            byte &= ~0x80;
            if (is_extended) {
                // uint8_t keycode = 0;
                // if (byte == 0x48) keycode = 0x3a;
                // if (byte == 0x4b) keycode = 0x37;
                // if (byte == 0x4d) keycode = 0x38;
                // if (byte == 0x50) keycode = 0x39;
                // if (keycode) kbd_state[keycode - 1] = pressed;
                // warning("todo ps2 ext {} {:#x}", *mode, byte);
                is_extended = false;
                continue;
            }
            if (byte == 0x36) {
                shift = pressed;
            }
            if (byte < sizeof(c1)) {
                char c = (shift?c2:c1)[byte];
                if (c && c != '\e' && pressed) return c;
                continue;
            } else {
                warning("todo ps2 norm {} {:#x}", *mode, byte);
            }
        }
    }
}
