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