///
///@file framebuffer.c
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

#include "framebuffer.h"

#include "cpu/bootloader.h"

#define PIXEL_WIDTH 0x4

struct Framebuffer framebuffer_initalise(BootloaderInfo_t *bl)
{
    struct stivale2_struct_tag_framebuffer *data = get_bootloader_tag(bl, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    
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
            .header = get_bootloader_tag(bl, STIVALE2_HEADER_TAG_FRAMEBUFFER_ID),
            .data   = data
        }
    };
}

void framebuffer_draw_pixel(struct Framebuffer *fb, Point_t pos, Colour_t colour)
{
    dword loc = pos.x * PIXEL_WIDTH + pos.y * fb->pitch;
    fb->pixels[loc]         = colour.blue   & 0xFF;
    fb->pixels[loc + 0x1]   = colour.green  & 0xFF;
    fb->pixels[loc + 0x2]   = colour.red    & 0xFF;
    fb->pixels[loc + 0x3]   = colour.alpha  & 0xFF;
}
