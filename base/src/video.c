#include "video.h"
#include <i86.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

static uint8_t far* video_buffer;
static uint8_t far* vga_buffer = (uint8_t far*) 0xA0000000;

static inline void _video_set_pixel(uint16_t x, uint16_t y, uint8_t color)
{
    video_buffer[y * SCREEN_WIDTH + x] = color;
}

void video_init()
{
    video_buffer = _fmalloc(SCREEN_WIDTH * SCREEN_HEIGHT);

    if (video_buffer == NULL)
    {
        loader_error("Could not initialize a double video buffer!");
        return;
    }

    video_clear();
}

void video_enter()
{
    union REGS regs;
    
    regs.w.ax = 0x0013;
    int86(0x10, &regs, &regs);
}

void video_exit()
{
    union REGS regs;

    regs.w.ax = 0x0003;
    int86(0x10, &regs, &regs);
}

void video_clear()
{
    _fmemset(video_buffer, 55, SCREEN_WIDTH * SCREEN_HEIGHT);
}

void video_draw_rect(
    uint16_t x0, uint16_t y0,
    uint16_t x1, uint16_t y1,
    uint8_t color
)
{
    uint16_t y;
    uint8_t far* ptr = video_buffer + y0 * SCREEN_WIDTH + x0;

    for (y = y0; y <= y1; y++)
    {
        _fmemset(ptr, color, x1 - x0 + 1);
        ptr += SCREEN_WIDTH;
    }
}

void video_draw_sprite(sprite_t __far* s, int16_t tx, int16_t ty)
{
    int16_t x, y;
    uint8_t pixel;

    /* TODO: optimization of sprite drawing routine
            (copying entire lines at once, more efficient clipping...) */

    for (x = tx; x < (tx + s->width); x++)
    {
        if (x < 0 || x >= SCREEN_WIDTH)
            continue;

        for (y = ty; y < (ty + s->height); y++)
        {
            if (y < 0 || y >= SCREEN_HEIGHT)
                continue;

            pixel = sprite_get_pixel(s, x - tx, y - ty);
            if (pixel == 255)
                continue;

            _video_set_pixel(x, y, pixel);
        }
    }
}

void video_render()
{
    _fmemcpy(vga_buffer, video_buffer, SCREEN_WIDTH * SCREEN_HEIGHT);
}

void video_cleanup()
{
    _ffree(video_buffer);
}
