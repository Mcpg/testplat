#include "input.h"
#include <bios.h>
#include <dos.h>
#include <i86.h>
#include "pic.h"
#include <string.h>

#define KEY_BUFFER_SIZE 48
static uint16_t _key_buffer[KEY_BUFFER_SIZE] = {0};
static uint8_t _key_buffer_top = 0;

static void interrupt (*_old_irq2)();

uint8_t input_any_key_pressed = 0;

uint16_t input_press_map[INPUT_AMOUNT] = {0};
uint16_t input_rel_map[INPUT_AMOUNT];

uint8_t input_just_pressed[INPUT_AMOUNT] = {0};
uint8_t input_pressed[INPUT_AMOUNT] = {0};

static void interrupt _irq1_handler(union INTPACK regs)
{
    static uint8_t partial_scancode = 0;

    uint8_t scancode;

    if (_key_buffer_top >= KEY_BUFFER_SIZE)
        return; /* uh oh buffer is fuuuuulll */

    scancode = inp(0x60);

    if (scancode == 0xE0)
    {
        partial_scancode = scancode;
        PIC0_EOI();
        return;
    }

    if (partial_scancode == 0)
    {
        _key_buffer[_key_buffer_top++] = scancode & 0xFF;
    }
    else
    {
        _key_buffer[_key_buffer_top++] = (partial_scancode << 8) | scancode;
        partial_scancode = 0;
    }
    
    PIC0_EOI();
}

static uint8_t _input_get_release_action(uint16_t scancode)
{
    uint8_t i;

    for (i = 0; i < INPUT_AMOUNT; i++)
    {
        if ((input_rel_map[i] & scancode) == scancode)
            return i;
    }

    return INPUT_AMOUNT;
}

static uint8_t _input_get_press_action(uint16_t scancode)
{
    uint8_t i;

    for (i = 0; i < INPUT_AMOUNT; i++)
    {
        if ((input_press_map[i] & scancode) == scancode)
            return i;
    }

    return INPUT_AMOUNT;
}

void input_init()
{
    /* TODO: load the input map from a file */
    /* NOTE: might not work if player holds the key with CTRL or ALT */

    /* Up arrow key */
    input_press_map[INPUT_UP]    = 0xE048;
    input_rel_map[INPUT_UP]      = 0xE0C8;
    
    /* Down arrow key */
    input_press_map[INPUT_DOWN]  = 0xE050;
    input_rel_map[INPUT_DOWN]    = 0xE0D0;
    
    /* Left arrow key */
    input_press_map[INPUT_LEFT]  = 0xE0CB;
    input_rel_map[INPUT_LEFT]    = 0xE0CB;

    /* Right arrow key */
    input_press_map[INPUT_RIGHT] = 0xE0CD;
    input_rel_map[INPUT_RIGHT]   = 0xE0CD;

    _old_irq2 = _dos_getvect(0x09);
    _dos_setvect(0x09, _irq1_handler);
}

void input_process()
{
    uint16_t scancode;
    uint8_t action;
    uint8_t i;

    memset(input_just_pressed, 0, sizeof(input_just_pressed));

    for (i = 0; i < _key_buffer_top; i++)
    {
        scancode = _key_buffer[i];
        
        action = _input_get_press_action(scancode);
        if (action != INPUT_AMOUNT)
        {
            input_just_pressed[action] = 1;
            input_pressed[action] = 1;
            continue;
        }

        action = _input_get_release_action(scancode);
        if (action != INPUT_AMOUNT)
        {
            input_pressed[action] = 0;
            continue;
        }
    }
    
    _key_buffer_top = 0;
}

void input_cleanup()
{
    _dos_setvect(0x09, _old_irq2);
}
