///
///@file framebuffer.h
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

#pragma once

#include "cpu/bootloader.h"

#include "common.h"
#include "utilities.h"


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


static inline struct Framebuffer Framebuffer_initalise(const BootloaderInfo_t *bl)
{
    struct stivale2_struct_tag_framebuffer *data = bootloader_find_tag(bl, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    return (struct Framebuffer) {
        .size           = { data->framebuffer_width, data->framebuffer_height },
        .bits_per_pixel = data->framebuffer_bpp,
        .memory_model   = data->memory_model,
        .pitch          = data->framebuffer_pitch,
        .pixels         = (byte *)data->framebuffer_addr,

        .masks = {
            .red    = { data->red_mask_shift,   data->red_mask_size },
            .green  = { data->green_mask_shift, data->green_mask_size },
            .blue   = { data->blue_mask_shift,  data->blue_mask_size },
        },

        .bootloader = {
            .header = bootloader_find_tag(bl, STIVALE2_HEADER_TAG_FRAMEBUFFER_ID),
            .data   = data
        }
    };
}

static void Framebuffer_draw_rect(const struct Framebuffer *fb, Rect_t rect, Colour_t colour)
{
    for (uint32 x = rect.position.x; x < rect.position.x + rect.size.x; x++) {
        for (uint32 y = rect.position.y; y < rect.position.y + rect.size.y; y++) {
            byte *draw = fb->pixels + (x * 0x4 + y * fb->pitch);
            draw[0] = colour.red & 0xFF;
            draw[1] = colour.green & 0xFF;
            draw[2] = colour.blue & 0xFF;
            draw[3] = colour.alpha & 0xFF;
        }
    }
}

static inline void Framebuffer_set_background(const struct Framebuffer *fb, Colour_t colour)
{ Framebuffer_draw_rect(fb, (Rect_t){ { 0, 0 }, fb->size }, colour); }

static inline void Framebuffer_draw_pixel(const struct Framebuffer *fb, Point_t pos, Colour_t colour)
{ 
    byte *draw = fb->pixels + (pos.x * 0x4 + pos.y * fb->pitch);
    draw[0] = colour.red & 0xFF;
    draw[1] = colour.green & 0xFF;
    draw[2] = colour.blue & 0xFF;
    draw[3] = colour.alpha & 0xFF;
}
