#include "resource.h"
#include <conio.h>
#include "debug.h"
#include "game.h"
#include <graph.h>
#include <i86.h>
#include "input.h"
#include <malloc.h>
#include "pit.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"
#include "video.h"

#define DEBUG

uint8_t sprite_amount;
sprite_t __far** sprites;

uint16_t sprite_segment_size;
uint8_t __far* sprite_segment;

static void _outtext_centered(int y, const char* text)
{
    int len = strlen(text);
    if (len > 80)
        return;
    
    _settextposition(y, 40 - len / 2);
    _outtext(text);
}

static void _outtext_ralign(int y, const char* text)
{
    int len = strlen(text);
    if (len > 80)
        return;
    
    _settextposition(y, 80 - len);
    _outtext(text);
}

static void _status(int y, const char* desc)
{
    _settextposition(y, 3);
    _settextcolor(0x09);
    _outtext("* ");
    _settextcolor(0x0F);
    _outtext(desc);

    uart_prints((char*) desc);
    uart_prints("\n");
}

static void _status_write_done()
{
    _settextcolor(0x0A);
    _outtext(" DONE");
}

void load_ui()
{
    int i;
    union REGS regs;
    
    /* TODO: cleanup loader UI's code and maybe move it to a separate file? */

    _setvideomode(_TEXTC80);
    regs.w.ax = 0x1003;
    regs.h.bl = 0x00;
    int86(0x10, &regs, &regs);
    
    _settextcolor(0x09);
    
    for (i = 1; i <= 80; i++)
    {
        _settextposition(1, i);
        _outtext("=");
        _settextposition(3, i);
        _outtext("=");
        _settextposition(24, i);
        _outtext("=");
    }
    
    _settextcolor(0x0E);
    _outtext_centered(2, "Unnamed game loader");
    
    _settextcolor(0x08);
    _outtext_ralign(25, "Version " VERSION);
    
    i = 3;

    _status(i += 2, "Initializing UART...");
    uart_init();
    _status_write_done();

    DPRINT1("Debug level: %d", DEBUG_LEVEL)

    _status(i += 2, "Loading sprites from SPRITES.DAT...");
    load_sprites();
    _status_write_done();
    
    _status(i += 2, "Loading animations from ANIM.DAT...");
    
    _status_write_done();
    
    _status(i += 2, "Loading tileset from TILESET.DAT...");
    
    _status_write_done();

    _status(i += 2, "Initializing video system...");
    video_init();
    _status_write_done();

    _status(i += 2, "Initializing input system...");
    input_init();
    _status_write_done();
    
    _status(i += 2, "Initializing PIT...");
    pit_init(PIT_60HZ);
    _status_write_done();
    
    video_enter();
    
}

void loader_error(const char* text)
{
    _settextcolor(0x0C);
    _outtext(" ERROR\n    ");
    _outtext(text);
    _settextposition(24, 0);
    exit(1);
}

#define SPRITE_BUFFER_SIZE 16

void load_sprites()
{
    FILE* f;
    uint8_t far* current_sprite;
    uint16_t offset = 0;
    uint16_t i;
    uint8_t buffer[SPRITE_BUFFER_SIZE];
    
    f = fopen(SPRITES_FILENAME, "rb");
    if (f == NULL)
    {
        loader_error("Could not open SPRITES.DAT!");
        return;
    }
    
    /* Read the sprite amount */
    if (fread(&sprite_amount, 1, 1, f) != 1)
    {
        loader_error("Incorrect format of SPRITES.DAT!");
        return;
    }
    
    /* Get the segment size */
    fseek(f, 0, SEEK_END);
    sprite_segment_size = ftell(f);
    fseek(f, 1, SEEK_SET);
    
    if (sprite_segment_size == 0)
    {
        fclose(f);
        return;
    }

    /* Align the segment size to 16 */
    if (sprite_segment_size & 0xF != 0)
    {
        sprite_segment_size &= ~0xF;
        sprite_segment_size += 16;
    }
    
    sprite_segment = _fmalloc(sprite_segment_size);
    if (!sprite_segment)
    {
        loader_error("Could not allocate enough memory for sprites!");
        return;
    }
    
    /* Read the sprite data and copy it into the sprite segment */
    do
    {
        i = fread(&buffer, SPRITE_BUFFER_SIZE, 1, f);
        _fmemcpy(sprite_segment + offset, buffer, SPRITE_BUFFER_SIZE);
        offset += SPRITE_BUFFER_SIZE;
    } while (i != 0);
    
    /* Create the array with sprite locations */
    sprites = (sprite_t __far**) malloc(sizeof(sprite_t __far*)*sprite_amount);
    current_sprite = sprite_segment;
    
    for (i = 0; i < sprite_amount; i++)
    {
        sprites[i] = (sprite_t __far*) current_sprite;

        current_sprite += sizeof(sprite_t)
                + sprites[i]->width * sprites[i]->height - 1;
    }
}

uint8_t sprite_get_pixel(sprite_t __far* s, int x, int y)
{
    if (x < 0 || y < 0 || x >= s->width || y >= s->height)
    {
        return ~0;
    }
    return s->data[(y * s->width) + x];
}

void resource_cleanup()
{
    _ffree(sprite_segment);
    free(sprites);
}
