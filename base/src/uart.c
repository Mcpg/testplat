#include "uart.h"
#include <conio.h>
#include "game.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void uart_init()
{
    /* TODO: potential UART cleanup after configuration? */
    outp(UART_PORT + 1, 0x00);
    outp(UART_PORT + 3, 0x80);
    outp(UART_PORT,     0x03);
    outp(UART_PORT + 1, 0x00);
    outp(UART_PORT + 3, 0x03);
    outp(UART_PORT + 2, 0xC7);
    outp(UART_PORT + 4, 0x0B);

    uart_prints("\n\n");
    uart_prints("Initialized UART controller\n");
    uart_printf(" Game version: %s\n", VERSION);
}

void uart_prints(char* text)
{
    uint16_t i;

    for (i = 0; text[i]; i++)
    {
        while ((inp(UART_PORT + 5) & 0x20) == 0) ;

        if (text[i] == '\n')
            uart_prints("\r");
        outp(UART_PORT, text[i]);
    }
}

void uart_printf(char* format, ...)
{
    char buffer[UART_STRING_BUFFER];
    int16_t amount;
    va_list vargs;

    memset(&buffer, 0x00, sizeof(buffer));

    va_start(vargs, format);
    amount = vsprintf(&buffer, format, vargs);
    uart_prints(&buffer);
    va_end(vargs);
}
