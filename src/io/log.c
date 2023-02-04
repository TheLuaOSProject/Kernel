/**
 * Copyright (C) 2023 Amrit Bhogal, pitust
 *
 * This file is part of LuaOS.
 *
 * LuaOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LuaOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdatomic.h>
#include <string.h>

#include "kern/io/log.h"
#include "kern/io/console.h"
#include "kern/io/port.h"
#include "common.h"

static atomic_bool console = true;
static atomic_bool e9 = false;
static atomic_bool serial = true;


static void output_char(char c) {
    if (atomic_load(&console)) console_write_char(c);
    if (atomic_load(&e9)) port_out_byte(0xe9, c);
    if (atomic_load(&serial)) {
        while ((port_in_byte(0x3fd) & 0x20) == 0) asm("pause");
        port_out_byte(0x3f8, c);
    }
}
static void output_string(const char* s) {
    while (*s) output_char(*s++);
}

typedef struct {
    char fill;
    char align;

    char sign;

    bool group;

    bool use_alt_form;

    char fill_char;
    unsigned int width;

    char type;
} format_specifier_t;

static format_specifier_t parse_fmt(const char** fmtref) {
#define current() (**fmtref)
#define next() (*fmtref)++;

    while (current()) {
        if (current() == '{') {
            next();
            if (current() == '{') {
                next();
                output_char('{');
            } else {
                goto scan;
            }
        } else if (current() == '}') {
            next();
            if (current() == '}') {
                output_char('}');
                next();
            } else {
                panic("expected '}}' after '}}', found '{}'", current());
            }
        } else {
            output_char(current());
            next();
        }
    }
    panic("unexpected end of input, expected another input line!");
scan:;
    format_specifier_t spec;
    spec.fill = ' ';
    spec.align = '>';

    spec.sign = '-';

    spec.group = false;

    spec.use_alt_form = false;

    spec.width = 0;

    spec.type = ' ';
    
    if (current() == ':') {
        if (
            current() != '<' && current() != '>' && current() != '^' // fill
            && current() != '+' && current() != '-' && current() != ' ' // sign
            && current() != '#' // alt mode
            && current() != '0' // 0 as fill character
            && (current() < '0' || current() > '9') // width
            && current() != '_' // grouping
            && current() != 'b' && current() != 'c' && current() != 'd' && current() != 'o' && current() != 'x' && current() != 'X' // type
        ) {
            // fill character
            spec.fill = current();
            next();
        }
        if (current() == '<' || current() == '>' || current() == '^') {
            spec.align = current();
            next();
        } else if (spec.fill != ' ') {
            panic("spec.fill de facto implies spec.align");
        }
        if (current() == '#') {
            spec.use_alt_form = true;
            next();
        }
        if (current() == '0') {
            spec.align = '0';
            spec.fill = '=';
            next();
        }
        if (current() >= '0' && current() <= '9') {
            int width = 0;
            while (current() >= '0' && current() <= '9') {
                width *= 10;
                width += current() - '0';
                next();
            }
            spec.width = width;
        }
        if (current() == '_') {
            spec.group = true;
            next();
        }
        if (
            current() == 'b' || current() == 'c' || current() == 'd' || current() == 'o'|| current() == 'x' || current() == 'X'
        ) {
            spec.type = current();
        }
    }
    if (current() != '}') {
        panic("expected '}}', found '{}'", current());
    }
    next();

#undef current
    return spec;
}

void _log_level_info(void) { output_string("\x1b[32minfo\x1b[0m "); }
void _log_level_err(void) { output_string("\x1b[31merr\x1b[0m "); }
void _log_level_panic(void) { output_string("\x1b[31mpanic\x1b[0m "); }
void _log_level_common_end(const char** fmtref) { output_string(*fmtref); output_char('\n'); }
void _log_level_panic_end(const char** fmtref) {
    output_string(*fmtref);
    output_char('\n');
    halt();
}

static void log_do_append_number(char** _buf, unsigned long long num, int base, bool upcase) {
#define buf (*_buf)
    if (!num) *--buf = '0';
    while (num) {
        *--buf = (upcase ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" : "0123456789abcdefghijklmnopqrstuvwxyz")[num % base];
        num /= base;
    }
#undef buf
}
static void log_emit(format_specifier_t fi, char* buf) {
    if (string_length(buf) < fi.width) {
        int wi_b = string_length(buf);
        int dis_b = wi_b - fi.width;
        int half_b = dis_b / 2;
        int half2_b = dis_b - half_b;
        if (fi.align == '>') {
            for (int i = 0;i < dis_b;i++) output_char(fi.fill);
        }
        if (fi.align == '^') {
            for (int i = 0;i < half2_b;i++) output_char(fi.fill);
        }
        output_string(buf);
        if (fi.align == '<') {
            for (int i = 0;i < dis_b;i++) output_char(fi.fill);
        }
        if (fi.align == '^') {
            for (int i = 0;i < half_b;i++) output_char(fi.fill);
        }
    } else {
        output_string(buf);
    }
}
static int log_num_base(format_specifier_t fi) {
    if (fi.type == ' ' || fi.type == 'd') return 10;
    if (fi.type == 'b') return 2;
    if (fi.type == 'c') panic("log_num_base() expects you to check for 'c' yourself!");
    if (fi.type == 'o') return 8;
    if (fi.type == 'x' || fi.type == 'X') return 16;
    panic("invalid type fi.type {}", fi.type);
}
static void log_num_u(format_specifier_t fi, unsigned long long num) {
    char _buf[64];
    char* buf = _buf + 64;
    *--buf = 0;
    if (fi.type == 'c') {
        if (fi.use_alt_form) *--buf = '\'';
        *--buf = num;
        if (fi.use_alt_form) *--buf = '\'';
        log_emit(fi, buf);
        return;
    }
    log_do_append_number(&buf, num, log_num_base(fi), fi.type == 'X');
    if (fi.sign == ' ') *--buf = ' ';
    if (fi.sign == '+') *--buf = '+';

    log_emit(fi, buf);
}
static void log_num_s(format_specifier_t fi, long long num) {
    char _buf[64];
    char* buf = _buf + 64;
    *--buf = 0;
    if (fi.type == 'c') {
        if (fi.use_alt_form) *--buf = '\'';
        *--buf = num;
        if (fi.use_alt_form) *--buf = '\'';
        log_emit(fi, buf);
        return;
    }
    if (num < 0) {
        log_do_append_number(&buf, -num, log_num_base(fi), fi.type == 'X');
        *--buf = '-';
    } else {
        log_do_append_number(&buf, num, log_num_base(fi), fi.type == 'X');
        if (fi.sign == ' ') *--buf = ' ';
        if (fi.sign == '+') *--buf = '+';
    }

    log_emit(fi, buf);
}

void _log_signed8(const char** fmtref, signed char num) { log_num_s(parse_fmt(fmtref), num); }
void _log_signed16(const char** fmtref, short num) { log_num_s(parse_fmt(fmtref), num); }
void _log_signed32(const char** fmtref, int num) { log_num_s(parse_fmt(fmtref), num); }
void _log_signedptr(const char** fmtref, long num) { log_num_s(parse_fmt(fmtref), num); }
void _log_signed64(const char** fmtref, long long num) { log_num_s(parse_fmt(fmtref), num); }
void _log_unsigned8(const char** fmtref, unsigned char num) { log_num_u(parse_fmt(fmtref), num); }
void _log_unsigned16(const char** fmtref, unsigned short num) { log_num_u(parse_fmt(fmtref), num); }
void _log_unsigned32(const char** fmtref, unsigned int num) { log_num_u(parse_fmt(fmtref), num); }
void _log_unsignedptr(const char** fmtref, unsigned long num) { log_num_u(parse_fmt(fmtref), num); }
void _log_unsigned64(const char** fmtref, unsigned long long num) { log_num_u(parse_fmt(fmtref), num); }
void _log_char(const char** fmtref, char c) {
    format_specifier_t fi = parse_fmt(fmtref);

    char _buf[64];
    char* buf = _buf + 64;
    if (fi.type != 'c' && fi.type != ' ') {
        panic("expected 'c' or nothing as fi.type, found {}", fi.type);
    }
    *--buf = 0;
    *--buf = c;

    log_emit(fi, buf);
}

