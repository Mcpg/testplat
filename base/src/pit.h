#ifndef _PIT_H
#define _PIT_H

typedef void (*pit_int_handler_t)();

extern void pit_init();
extern void pit_hook(pit_int_handler_t handler);
extern void pit_reset();

#endif
