#ifndef _PIC_H
#define _PIC_H

#define PIC0_COMMAND 0x20
#define PIC_EOI_CMD  0x20

#include <conio.h>

#define PIC0_EOI() outp(PIC0_COMMAND, PIC_EOI_CMD)

#endif
