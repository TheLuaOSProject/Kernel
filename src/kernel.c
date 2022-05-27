#include "utilities.h"
#include "cpu/bootloader.h"
#include "drivers/framebuffer.h"

ATTRIBUTE(noreturn, used)
int kernel_start(BootloaderInfo_t *bootloader)
{
    struct FramebufferInfo fb = {
        .header = get_bootloader_tag(bootloader, STIVALE2_HEADER_TAG_FRAMEBUFFER_ID),
        .data = get_bootloader_tag(bootloader, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID)
    };
    framebuffer_initalise(fb);
    
    HALT();
}
