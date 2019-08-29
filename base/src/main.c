#include "resource.h"
#include <stdio.h>
#include "video.h"
#include <stddef.h>
#include <graph.h>
#include <string.h>

extern void hang();
#pragma aux hang = \
    "cli" \
    "hlt";

int main(int argc, char* argv[])
{
    load_ui();

    video_clear();
    video_draw_sprite(sprites[0], 10, 10);
    video_render();
    

    hang();
    video_exit();
    return 0;
}
