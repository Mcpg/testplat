#ifndef _INPUT_H
#define _INPUT_H

#include <stdint.h>

enum input_action
{
    INPUT_UP     = 0,
    INPUT_DOWN   = 1,
    INPUT_LEFT   = 2,
    INPUT_RIGHT  = 3,

    INPUT_AMOUNT = 4
};
typedef enum input_action input_action_t;

extern uint8_t input_any_key_pressed;

/* Each scancode "activating" a key */
extern uint16_t input_press_map[INPUT_AMOUNT];
/* Each scancode releasing a key */
extern uint16_t input_rel_map[INPUT_AMOUNT];

/* Each key pressed during last execution of input_process */
extern uint8_t input_just_pressed[INPUT_AMOUNT];
/* Each currently pressed key mapped as 0/1 value */
extern uint8_t input_pressed[INPUT_AMOUNT];

extern void input_init();
extern void input_process();
extern void input_cleanup();

#endif
