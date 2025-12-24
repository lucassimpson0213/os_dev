#include <stdio.h>
#include <stdint.h>
#include "gdt.h"


typedef unsigned short ushort;
static inline void
lgdt(struct segdesc *p, int size)
{
    volatile ushort pd[3];

    pd[0] = size - 1;
    pd[1] = (uint)p;
    pd[2] = (uint)p >> 16;

    asm volatile("lgdt (%0)" : : "r"(pd));
}

void init_gdt() {
    struct segdesc gdt[5];
    gdt[SEG_KCODE] = SEG(STA_X | STA_R, 0, 0xffffffff, 0);
    gdt[SEG_KDATA] = SEG(STA_W, 0, 0xffffffff, 0);
    gdt[SEG_UCODE] = SEG(STA_X | STA_R, 0, 0xffffffff, DPL_USER);
    gdt[SEG_UDATA] = SEG(STA_W, 0, 0xffffffff, DPL_USER);

    lgdt(gdt, sizeof(gdt));


}

