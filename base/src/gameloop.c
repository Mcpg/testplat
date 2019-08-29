#include "gameloop.h"
#include "game.h"
#include <stdlib.h>
#include "video.h"

uint8_t game_running = 0;

static uint8_t loop_in_progress = 0;
static uint16_t dropped_frames = 0;

void game_loop()
{
    if (!game_running)
        return;

    if (loop_in_progress)
    {
        dropped_frames++;
        return;
    }

    loop_in_progress = 1;
    video_clear();

    video_render();
    loop_in_progress = 0;
}
