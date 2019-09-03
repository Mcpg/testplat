#ifndef _UART_H
#define _UART_H

#include "debug.h"

#define UART_PORT 0x3F8 /* COM1 */
#define UART_STRING_BUFFER 512

extern void uart_init();
extern void uart_prints(const char* text);
extern void uart_printf(const char* format, ...);

#endif
