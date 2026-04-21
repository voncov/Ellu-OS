#include "stdint.h"
#include <gdt.h>

struct E_GDT_ENTRY gdt[5];
struct E_GDT_PTR gdt_ptr;

extern VOID gdt_Load(struct E_GDT_PTR *rdi);

VOID gdt_SetEntry(INT32 num, UINT32 base, UINT32 limit, UINT8 access, UINT8 granularity)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].access = access;
}

VOID gdt_Init()
{
    gdt_SetEntry(0, 0, 0, 0, 0);
    gdt_SetEntry(1, 0, 0xFFFFF, 0x9A, 0xA0);
    gdt_SetEntry(2, 0, 0xFFFFF, 0x92, 0xC0);
    gdt_SetEntry(3, 0, 0xFFFFF, 0xFA, 0xA0);
    gdt_SetEntry(4, 0, 0xFFFFF, 0xF2, 0xC0);

    gdt_ptr.limit = (sizeof(struct E_GDT_ENTRY) * 5) - 1;
    gdt_ptr.base = (UINT64)&gdt;

    gdt_Load(&gdt_ptr);
}