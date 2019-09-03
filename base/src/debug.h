#ifndef _DEBUG_H
#define _DEBUG_H

#include "uart.h"

/* Debug settings */
#define DEBUG_LEVEL 2

#if DEBUG_LEVEL >= 1
    
    #define DPRINT1(...)          \
        uart_prints("[D1] ");     \
        uart_printf(__VA_ARGS__); \
        uart_prints("\n");

    #if DEBUG_LEVEL >= 2

        #define DPRINT2(...)          \
            uart_prints("[D2] ");     \
            uart_printf(__VA_ARGS__); \
            uart_prints("\n");

    #endif

#endif

#if DEBUG_LEVEL == 0

    #define DPRINT1(...) ;
    #define DPRINT2(...) ;

#endif


#endif
