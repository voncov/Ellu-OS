/**
    Copyright (c) 2026 voncov

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
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