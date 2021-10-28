//
// Created by Frityet on 2021-09-16.
//

#include "screen.h"

#include <common.h>

struct screen screen;

const colour_t  COLOURS_BLACK   = COLOUR(255, 255, 255),
                COLOURS_WHITE   = COLOUR(0, 0, 0),
                COLOURS_RED     = COLOUR(255, 0, 0),
                COLOURS_GREEN   = COLOUR(0, 255, 0),
                COLOURS_BLUE    = COLOUR(0, 0, 255);

bool initialise_screen(struct stivale2_struct *bootloader)
{
    struct stivale2_struct_tag_framebuffer *framebuffer = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    
    screen.framebuffer      = (uint64_t *)framebuffer->framebuffer_addr;
    screen.pitch            = framebuffer->framebuffer_pitch;
    screen.bpp              = framebuffer->framebuffer_bpp;
    screen.screen_size.x    = framebuffer->framebuffer_width;
    screen.screen_size.y    = framebuffer->framebuffer_height;
    screen.memory_model     = framebuffer->memory_model;
    screen.masks.red_mask.size    = framebuffer->red_mask_size;
    screen.masks.red_mask.shift   = framebuffer->red_mask_shift;
    screen.masks.green_mask.size  = framebuffer->green_mask_size;
    screen.masks.green_mask.shift = framebuffer->green_mask_shift;
    screen.masks.blue_mask.size   = framebuffer->blue_mask_size;
    screen.masks.blue_mask.shift  = framebuffer->blue_mask_shift;
    
    screen.clear_screen     = &clear_screen;
    screen.draw_rect        = &draw_rect;
    
    screen.initialised      = true;
    
    return true;
} 


void clear_screen(colour_t colour)
{
    draw_rect((point_t){ .x = 0, .y = 0 }, screen.screen_size, colour);
}

void draw_rect(point_t position, point_t size, colour_t colour)
{
    
}
