//
// Created by Frityet on 2021-09-16.
//

#include "screen.h"

#include <common.h>
#include <stdbool.h>
#include <stdint.h>

struct screen screen;

const colour_t  COLOURS_BLACK   = COLOUR(255, 255, 255),
                COLOURS_WHITE   = COLOUR(0, 0, 0),
                COLOURS_RED     = COLOUR(255, 0, 0),
                COLOURS_GREEN   = COLOUR(0, 255, 0),
                COLOURS_BLUE    = COLOUR(0, 0, 255);

const uint8_t PIXEL_WIDTH = sizeof(uint64_t);

static void clear_screen(colour_t colour);

static void draw_rect(point_t   position,
                      point_t   size,
                      colour_t  colour);

bool initialise_screen(struct stivale2_struct *bootloader)
{
    struct stivale2_struct_tag_framebuffer *framebuffer = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    screen = (struct screen) {
        .framebuffer        = (uint64_t *)framebuffer->framebuffer_addr,
        .pitch              = framebuffer->framebuffer_pitch,
        .bpp                = framebuffer->framebuffer_bpp,
        .screen_size.x      = framebuffer->framebuffer_width,
        .screen_size.y      = framebuffer->framebuffer_height,
        .memory_model       = framebuffer->memory_model,

        .masks = {
            .red = {
                .shift  = framebuffer->red_mask_shift,
                .size   = framebuffer->red_mask_size
            },
            .green = {
                .shift  = framebuffer->green_mask_shift,
                .size   = framebuffer->green_mask_size
            },
            .blue = {
                .shift  = framebuffer->blue_mask_shift,
                .size   = framebuffer->blue_mask_size
            }
        },
    
        .clear_screen   = &clear_screen,
        .draw_rect      = &draw_rect,

        .initialised = true
    };
    
    return true;
} 


void clear_screen(colour_t colour)
{
    draw_rect(POINT(0, 0), screen.screen_size, colour);
}

void draw_rect(UNUSED point_t position, point_t size, colour_t colour)
{
    uint64_t *framebuffer = screen.framebuffer;
    for (uint32_t i = 0; i < size.x; ++i) {
        for (uint32_t j = 0; j < size.y; ++j) {
            framebuffer[j * PIXEL_WIDTH]        = colour.red;
            framebuffer[j * PIXEL_WIDTH + 1]    = colour.green;
            framebuffer[j * PIXEL_WIDTH + 2]    = colour.blue;
        }
        framebuffer += screen.pitch;
    }
}
