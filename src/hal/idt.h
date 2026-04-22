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
#ifndef IDT_H
#define IDT_H
#pragma once

#include <stdint.h>
#include <stddef.h>

struct E_IDT_ENTRY {
    UINT16 offset_low;
    UINT16 selector;
    UINT8 ist;
    UINT8 type_attr;
    UINT16 offset_mid;
    UINT32 offset_high;
    UINT32 zero;
} __attribute__((packed));

struct E_IDT_PTR {
    UINT16 limit;
    UINT64 base;
} __attribute__((packed));

VOID idt_SetGate(INT32 num, VOID (*handler)(), UINT8 type_attr);
VOID idt_Init();

#endif