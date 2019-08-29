#ifndef _VIDEO_H
#define _VIDEO_H

#include "resource.h"
#include <stdint.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

extern void video_init();
extern void video_enter();
extern void video_exit();

extern void video_clear();
extern void video_draw_rect(
    uint16_t x0, uint16_t y0,
    uint16_t x1, uint16_t y1,
    uint8_t color
);
extern void video_draw_sprite(sprite_t __far* s, int16_t tx, int16_t ty);

extern void video_render();

extern void video_cleanup();

#endif
