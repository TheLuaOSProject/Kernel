/**
 * @file    screen.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Interface with the framebuffer provided by Limine
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */

#ifndef LUAOS_SCREEN
#define LUAOS_SCREEN

#include <common.h>

#define POINT(_x, _y)           (point_t){ .x = (_x), .y = (_y) }
#define ENUMERATE_SCREEN()      for (int x = 0, y = 0; x < screen.screen_size.x, y < screen.screen_size.y; ++x, ++y)
typedef struct {
    uint32_t    x;
    uint32_t    y;
} point_t;


#define COLOUR(r, g, b) (colour_t){ .red = (r), .green = (g), .blue = (b) }
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

static void draw_rect(point_t   position,
                      point_t   size,
                      colour_t  colour);

#endif //LUAOS_SCREEN
