#include "loadui.h"
#include <graph.h>
#include "resource.h"
#include <stdio.h>

void load_game()
{
    /* Jump to 80x25 text mode with 16 colors
       (and clear the screen) */
    //_setvideomode(_TEXTC80);
    
    printf("Loading game data... ");
    load_data();
    printf("done\n");
    printf("DBG: Loaded %d data node(s).\n", data_node_amount);
    
}
