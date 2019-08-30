#include "gameloop.h"
#include "game.h"
#include "input.h"
#include "pit.h"
#include "resource.h"
#include <stdlib.h>
#include "video.h"

void shutdown()
{
    video_exit();
    video_cleanup();
    input_cleanup();
    pit_reset();
    exit(0);
}

int main(int argc, char* argv[])
{
    load_ui();

    game_running = 1;
    pit_hook(game_loop);

    /* While the game is running, keep on halting the CPU until IRQ0 is fired.
       Game's logic is handled there. */
    while (game_running)
    {
        _asm {
            hlt
        }
    }

    shutdown();
    return 0;
}
