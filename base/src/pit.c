#include "pit.h"
#include <conio.h>
#include <dos.h>
#include <i86.h>
#include "pic.h"
#include <stddef.h>
#include <stdint.h>

#define PIT_CHANNEL_0 0x40
#define PIT_CHANNEL_2 0x42
#define PIT_MCR       0x43

static pit_int_handler_t current_handler = NULL;
static uint32_t _old_irq0;

static void interrupt _pit_irq0(union INTPACK regs)
{
    if (current_handler)
        current_handler();

    PIC0_EOI(); /* IRQ0 EOI */
}

void pit_init(uint16_t timer_divider)
{
    _asm { cli }

    _old_irq0 = (uint32_t) _dos_getvect(0x08);
    _dos_setvect(0x08, _pit_irq0);

    /* Channel 0, write low and high byte for mode 2 */
    outp(PIT_MCR, 0x34);
    outp(PIT_CHANNEL_0, timer_divider & 0xFF);
    outp(PIT_CHANNEL_0, (timer_divider >> 8) & 0xFF);

    _asm { sti }
}

void pit_hook(pit_int_handler_t handler)
{
    current_handler = handler;
}

void pit_reset()
{
    /* Reset the PIT to the standard channel 0 (65536, 18.2 Hz) */
    outp(PIT_MCR, 0x34);
    outp(PIT_CHANNEL_0, 0x00);
    outp(PIT_CHANNEL_0, 0x00);

    _dos_setvect(0x08, (void (interrupt *)()) _old_irq0);
}
