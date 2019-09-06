#include "benchmrk.h"
#include "pit.h"

static uint8_t benchmark_in_progress = 0;
static uint16_t benchmark_current_amount = 0;

static void _benchmark_handler()
{
    benchmark_current_amount++;
}

uint16_t benchmark_function(void (*function)())
{
    uint16_t retval;

    if (benchmark_in_progress)
        return ~0;

    benchmark_in_progress = 1;
    
    pit_init(1193);
    pit_hook(_benchmark_handler);
    function();

    retval = benchmark_current_amount;
    benchmark_in_progress = 0;
    pit_reset();
    return retval;
}
