#include "utilities.h"
#include "cpu/bootloader.h"
#include "drivers/framebuffer.h"

ATTRIBUTE(noreturn, used)
void kernel_start(BootloaderInfo_t *bootloader)
{
    struct Framebuffer fb = framebuffer_initalise(bootloader);

    uint32 x = fb.size.x / 2, y = fb.size.y / 2;
    framebuffer_draw_pixel(&fb, POINT(x, y), COLOUR(0xA, 0xA, 0xA));
    framebuffer_draw_rect(&fb, RECT(x, y, 100, 100), COLOUR(0xFF, 0xFF, 0xFF));
    
    HALT();
}
