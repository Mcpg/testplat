#include "gameloop.h"
#include "benchmrk.h"
#include "game.h"
#include "input.h"
#include "pit.h"
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    uint16_t benchmark_time;

    if (argc > 1 && strcmp("/BENCHVC", argv[1]) == 0)
    {
        video_init();
        printf("Benchmarking video_clear...\n");
        printf("Benchmark done. Result: around %d millis\n",
            benchmark_function(video_clear));
        return 0;
    }

    if (argc > 1 && strcmp("/BENCHVR", argv[1]) == 0)
    {
        video_init();
        video_clear();
        video_enter();
        benchmark_time = benchmark_function(video_render);
        video_exit();
        printf("Benchmarking video_render with cleared buffer...\n");
        printf("Benchmark done. Result: around %d millis\n", benchmark_time);
        return 0;
    }

    load_ui();
    game_loop();
    shutdown();
    return 0;
}
