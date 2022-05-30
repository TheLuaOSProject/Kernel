#include "utilities.h"
#include "cpu/bootloader.h"
#include "drivers/framebuffer.h"
#include "drivers/qemu_log.h"

ATTRIBUTE(noreturn, used)
void kernel_start(BootloaderInfo_t *bootloader)
{
    struct QemuLog qlog = QemuLog_initalise(bootloader);
    QEMU_LOG(&qlog, "Launched kernel!");
    
    struct Framebuffer fb = Framebuffer_initalise(bootloader);
    QEMU_LOG(&qlog, "Initalised framebuffer!");

    Framebuffer_set_background(&fb, COLOUR(0xFF, 0xFF, 0xFF));
    
    uint32 x = fb.size.x / 2, y = fb.size.y / 2;
    
    Framebuffer_draw_rect(&fb, RECT(x, y, 100, 100), COLOUR(0xAA, 0x0, 0xF0));
    
    HALT();
}
