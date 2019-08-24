#ifndef _SPRITE_H
#define _SPRITE_H

#include "resource.h"

/* x and y can be negative or too high, the sprite will be clipped as needed */
void sprite_draw(sprite_t* sprite, int x, int y);

#endif
