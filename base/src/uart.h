#ifndef _UART_H
#define _UART_H

#define UART_PORT 0x3F8 /* COM1 */
#define UART_STRING_BUFFER 512

extern void uart_init();
extern void uart_prints(char* text);
extern void uart_printf(char* format, ...);

#endif
