///
///@file framebuffer.h
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

#pragma once

#include "cpu/bootloader.h"

#include "common.h"

typedef struct Point { dword x, y; } Point_t;
typedef struct Colour { byte red, green, blue, alpha; } Colour_t;

struct Framebuffer {
    Point_t size;
    word    bits_per_pixel,
            pitch;
    byte    memory_model;
    byte    *pixels;
    
    struct {
        struct  { byte size, shift; } red;
        struct  { byte size, shift; } green;
        struct  { byte size, shift; } blue;
    } masks;
    
    struct {
        struct stivale2_header_tag_framebuffer *header;
        struct stivale2_struct_tag_framebuffer *data;
    } bootloader;
};


struct Framebuffer framebuffer_initalise(BootloaderInfo_t *bl);

void framebuffer_draw_pixel(struct Framebuffer *fb, Point_t point, Colour_t colour);

static force_inline dword colour_to_dword(Colour_t col)
{
    return (col.alpha << 24) | (col.red << 16) | (col.green << 8) | col.blue;
//    byte b[4] = { col.red, col.green, col.blue, col.alpha };
//    return *(dword *)b; //fuck strict aliasing
}
