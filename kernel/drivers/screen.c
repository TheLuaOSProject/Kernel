//
// Created by Frityet on 2021-09-16.
//

#include "screen.h"

#include <common.h>

struct screen screen;

bool initialise_screen(struct stivale2_struct *bootloader)
{
    struct stivale2_struct_tag_framebuffer *framebuffer = get_stivale_tag(bootloader, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    
    screen.framebuffer      = (uint64_t *)framebuffer->framebuffer_addr;
    screen.pitch            = framebuffer->framebuffer_pitch;
    screen.bpp              = framebuffer->framebuffer_bpp;
    screen.screen_size.x    = framebuffer->framebuffer_width;
    screen.screen_size.y    = framebuffer->framebuffer_height;
    screen.memory_model     = framebuffer->memory_model;
    screen.red_mask.size    = framebuffer->red_mask_size;
    screen.red_mask.shift   = framebuffer->red_mask_shift;
    screen.green_mask.size  = framebuffer->green_mask_size;
    screen.green_mask.shift = framebuffer->green_mask_shift;
    screen.blue_mask.size   = framebuffer->blue_mask_size;
    screen.blue_mask.shift  = framebuffer->blue_mask_shift;

    clear_screen(0x8075FF);
    
    screen.clear_screen     = &clear_screen;
    screen.draw_rect        = &draw_rect;
    screen.set_pixel        = &set_pixel;
    
    screen.initialised      = true;
    
    return true;
} 

struct screen get_screen()
{
    return screen;
}

void clear_screen(uint32_t colour)
{
    point_t pos = { 0, 0 };
    draw_rect(pos, screen.screen_size, colour);
}

void set_pixel(point_t position, uint32_t colour)
{
    if (position.x >= screen.cursor_position.x || position.y >= screen.cursor_position.y) return;
    screen.framebuffer[position.y * (screen.pitch / 4) + position.x] = colour;
}

void draw_rect(point_t position, point_t size, uint32_t colour)
{
    screen.cursor_position = position;
    
    for (int height = 0; height < size.y; ++height) {
        for (int width = 0; width < size.x; ++width) {
            //TODO: find out what the fuck this means
            screen.framebuffer[screen.cursor_position.y * (screen.pitch / 4)] = colour;
            screen.cursor_position.x++;
        }
        screen.cursor_position.x = position.x;
        screen.cursor_position.y++;
    }
    
    screen.cursor_position.x = 0;
    screen.cursor_position.y = 0;
}
