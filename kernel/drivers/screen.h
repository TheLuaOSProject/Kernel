//
// Created by Frityet on 2021-09-16.
//

#ifndef LUAOS_SCREEN
#define LUAOS_SCREEN

#include <common.h>

typedef struct {
    uint32_t    x;
    uint32_t    y;
} point_t;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} colour_t;

extern const colour_t   COLOURS_BLACK,
                        COLOURS_WHITE,
                        COLOURS_RED,
                        COLOURS_GREEN,
                        COLOURS_BLUE;

#define COLOUR(r, g, b) (colour_t){ .red = (r), .green = (g), .blue = (b) } 

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
    
    struct { 
        struct mask red_mask;
        struct mask green_mask;
        struct mask blue_mask; 
    } masks;
    
    void        (*clear_screen) (colour_t colour);
    void        (*draw_rect)    (point_t        position,
                                 point_t        size,
                                 colour_t       colour);
    bool        initialised;
} screen;

bool initialise_screen(struct stivale2_struct *bootloader);

static void clear_screen(colour_t colour);
static void draw_rect(  point_t     position, 
                        point_t     size, 
                        colour_t    colour);

#endif //LUAOS_SCREEN
