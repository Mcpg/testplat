#ifndef _BENCHMRK_H
#define _BENCHMRK_H

#include <stdint.h>

/* Returns function's runtime in millis */
uint16_t benchmark_function(void (*function)());

#endif
