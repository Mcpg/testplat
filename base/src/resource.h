#ifndef _RESOURCE_H
#define _RESOURCE_H

#define PALETTE_FILENAME "PALETTE.DAT"
#define SPRITES_FILENAME "SPRITES.DAT"

#include <stdint.h>

/* See data/README.md for a little documentation of the formats */

_Packed struct sprite
{
    int8_t  width;
    int8_t  height;
    char     name[8];
    uint8_t  data[1];
};
typedef struct sprite sprite_t;

extern uint8_t sprite_amount;
extern sprite_t __far** sprites;

extern uint16_t sprite_segment_size;
extern uint8_t __far* sprite_segment;

extern void load_ui();
extern void load_ega_palette();
extern void load_sprites();
extern void loader_error(const char*);

extern uint8_t sprite_get_pixel(sprite_t __far* s, int x, int y);

#endif
