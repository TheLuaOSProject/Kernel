#include "utilities.h"
#include "cpu/bootloader.h"
#include "drivers/framebuffer.h"

ATTRIBUTE(noreturn, used)
void kernel_start(BootloaderInfo_t *bootloader)
{
    struct Framebuffer fb = framebuffer_initalise(bootloader);

//    Colour_t colour = {0};
    
//    uint8   *vals[] = { &colour.red, &colour.green, &colour.blue },
//            selector = 0;
//
//    for (uint32 x = 0; x < fb.size.x; x++) {
//        for (uint32 y = 0; y < fb.size.y; y++) {
//            uint32 *pix = (uint32 *)(fb.pixels + (x * 0x4 + y * fb.pitch));
//            *pix = colour_to_u32(colour);
//        }
//    }
    
    
    framebuffer_set_background(&fb, COLOUR(0xFF, 0xFF, 0xFF));
    
    uint32 x = fb.size.x / 2, y = fb.size.y / 2;
    
    framebuffer_draw_rect(&fb, RECT(x, y, 100, 100), COLOUR(0xAA, 0x0, 0xF0));
    
    HALT();
}
