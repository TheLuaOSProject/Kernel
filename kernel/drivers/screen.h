//
// Created by Frityet on 2021-09-16.
//

#ifndef LUAOS_SCREEN
#define LUAOS_SCREEN

#include <common.h>

typedef struct {
    int     x;
    int     y;
} point_t;

struct mask {
    uint8_t     size;
    uint8_t     shift;
};

extern struct screen {
    uint64_t    *framebuffer;
    uint32_t    pitch;
    uint32_t    bpp;
    point_t     screen_size;
    point_t     cursor_position;
    uint8_t     memory_model;
    struct mask red_mask;
    struct mask green_mask;
    struct mask blue_mask;
    
    void        (*clear_screen) (uint32_t colour);
    void        (*set_pixel)    (point_t position, uint32_t colour);
    void        (*draw_rect)    (point_t      position,
                                 point_t      size,
                                 uint32_t     colour);
    bool        initialised;
} screen;

bool initialise_screen(struct stivale2_struct *bootloader);

static void clear_screen(uint32_t colour);
static void set_pixel(point_t position, uint32_t colour);
static void draw_rect(  point_t     position, 
                        point_t     size, 
                        uint32_t    colour);

#endif //LUAOS_SCREEN
