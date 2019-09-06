#ifndef _PIT_H
#define _PIT_H

#include <stdint.h>

#define PIT_60HZ 19886 /* Equals to roughly 60 Hz */

typedef void (*pit_int_handler_t)();

extern void pit_init(uint16_t timer_divider);
extern void pit_hook(pit_int_handler_t handler);
extern void pit_reset();

#endif
