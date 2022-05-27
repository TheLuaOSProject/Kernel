///
///@file framebuffer.h
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

#pragma once

#include "cpu/bootloader.h"

#include "common.h"

#define POINT(_x, _y) (Point_t){ .x = (_x), .y = (_y) }
typedef struct Point { uint32 x, y; } Point_t;

#define RECT(_x, _y, _w, _h) (Rect_t) { .position = POINT(_x, _y), .size = POINT(_w, _h) } 
typedef struct Rectangle { Point_t position; Point_t size; } Rect_t;
    
#define COLOUR(_r, _g, _b, ...) (Colour_t){ .red = (_r), .green = (_g), .blue = (_b), .alpha = (0xFF __VA_OPT__(- 0xFF + ) __VA_ARGS__) }
typedef struct Colour { byte red, green, blue, alpha; } Colour_t;

struct Framebuffer {
    Point_t size;
    uint16  bits_per_pixel, pitch;
    byte    memory_model, *pixels;
    
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
void framebuffer_draw_rect(struct Framebuffer *fb, Rect_t rect, Colour_t colour);

pure static force_inline uint32 colour_to_u32(Colour_t col)
{
    return (col.alpha << 24) | (col.red << 16) | (col.green << 8) | col.blue;
}
