#include "gameloop.h"
#include "game.h"
#include "input.h"
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
        /* This shouldn't happen because of how a 8259 PIC behaves. I'm gonna
           leave it here regardless, just in case. */
        return;
    }

    loop_in_progress = 1;

    /* Logic update */
    input_process();

    

    /* Video update */
    video_clear();
    video_render();



    loop_in_progress = 0;
}
