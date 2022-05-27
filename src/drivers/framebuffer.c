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

void framebuffer_draw_pixel(struct Framebuffer *fb, Point_t pos, Colour_t colour)
{
    uint32 *pix = (uint32 *)(fb->pixels + (pos.x * PIXEL_WIDTH + pos.y * fb->pitch));
    *pix = colour_to_u32(colour);
}

void framebuffer_draw_rect(struct Framebuffer *fb, Rect_t rect, Colour_t colour)
{
    for (uint32 x = rect.position.x; x < rect.position.x + rect.size.x; x++) {
        for (uint32 y = rect.position.y; y < rect.position.y + rect.size.y; y++) {
            uint32 *pix = (uint32 *)(fb->pixels + (x * PIXEL_WIDTH + y * fb->pitch));
            *pix = colour_to_u32(colour);
        }
    }
}
