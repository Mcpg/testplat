#include "gameloop.h"
#include "debug.h"
#include "game.h"
#include "input.h"
#include "pit.h"
#include <stdlib.h>
#include "video.h"

uint8_t game_running = 0;

static uint8_t can_update = 0;
static uint8_t frame_in_progress = 0;

static uint16_t frames_processed = 0;
static uint16_t dropped_frames = 0;
static uint16_t dropped_frames_total = 0;

static void _game_loop_tick()
{
    can_update = 1;

    if (frame_in_progress)
    {
        dropped_frames++;
        dropped_frames_total++;
    }
}

static void game_loop_frame()
{
    if (!game_running || frame_in_progress)
        return;

    frame_in_progress = 1;

    /* Logic update, should take up to 6 ms :-) */
    input_process();

    /* Video update, will take around 10 ms :-( */
    video_render();

    frame_in_progress = 0;
}

void game_loop()
{
    uart_prints("Starting the game_loop...\n");

    game_running = 1;
    pit_hook(_game_loop_tick);

    while (game_running)
    {
        if (!can_update)
        {
            _asm { hlt }
            continue;
        }
        game_loop_frame();

        frames_processed++;

        if ((frames_processed % 60) == 0 && dropped_frames > 0)
        {
            DPRINT1("game_loop: dropped frames during last 60 iterations! df=%d, dft=%d",
                    dropped_frames, dropped_frames_total);
        }

        dropped_frames = 0;
        can_update = 0;
    }
}
