#include "com.h"

#define COM1 0x3f8

static inline VOID outb(UINT16 port, UINT8 val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline UINT8 inb(UINT16 port)
{
    UINT8 ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

VOID com_SerialInitE()
{
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}

INT32 com_IsTransmitEmptyE()
{
    return inb(COM1 + 5) & 0x20;
}

VOID com_PutCE(CHAR a)
{
    while (com_IsTransmitEmptyE() == 0);
    outb(COM1, a);
}

VOID com_PrintE(const CHAR* s)
{
    while (*s) {
        com_PutCE(*s++);
    }
}

VOID com_PrintHexE(UINT64 val)
{
    const CHAR hex[] = "0123456789ABCDEF";
    com_PrintE("0x");
    for (INT32 i = 60; i >= 0; i -= 4) {
        com_PutCE(hex[(val >> i) & 0xF]);
    }
}