#include "stdint.h"
#include <stddef.h>
#include <idt.h>

struct E_IDT_ENTRY idt[256];
struct E_IDT_PTR idt_ptr;

VOID idt_SetGate(INT32 num, VOID (*handler)(), UINT8 type_attr)
{
    UINT64 addr = (UINT64)handler;
    idt[num].offset_low = (UINT16)(addr & 0xFFFF);
    idt[num].selector = 0x08;
    idt[num].ist = 0;
    idt[num].type_attr = type_attr;
    idt[num].offset_mid = (UINT16)((addr >> 16) & 0xFFFF);
    idt[num].offset_high = (UINT32)((addr >> 32) & 0xFFFFFFFF);
    idt[num].zero = 0;
}

VOID idt_Init()
{
    extern VOID isr0();
    extern VOID isr1();
    extern VOID isr2();
    extern VOID isr3();
    extern VOID isr4();
    extern VOID isr5();
    extern VOID isr6();
    extern VOID isr7();
    extern VOID isr8();
    extern VOID isr9();
    extern VOID isr10();
    extern VOID isr11();
    extern VOID isr12();
    extern VOID isr13();
    extern VOID isr14();
    extern VOID isr15();
    extern VOID isr16();
    extern VOID isr17();
    extern VOID isr18();
    extern VOID isr19();
    extern VOID isr20();
    extern VOID isr21();
    extern VOID isr22();
    extern VOID isr23();
    extern VOID isr24();
    extern VOID isr25();
    extern VOID isr26();
    extern VOID isr27();
    extern VOID isr28();
    extern VOID isr29();
    extern VOID isr30();
    extern VOID isr31();

    idt_SetGate(0, isr0, 0x8E);
    idt_SetGate(1, isr1, 0x8E);
    idt_SetGate(2, isr2, 0x8E);
    idt_SetGate(3, isr3, 0x8E);
    idt_SetGate(4, isr4, 0x8E);
    idt_SetGate(5, isr5, 0x8E);
    idt_SetGate(6, isr6, 0x8E);
    idt_SetGate(7, isr7, 0x8E);
    idt_SetGate(8, isr8, 0x8E);
    idt_SetGate(9, isr9, 0x8E);
    idt_SetGate(10, isr10, 0x8E);
    idt_SetGate(11, isr11, 0x8E);
    idt_SetGate(12, isr12, 0x8E);
    idt_SetGate(13, isr13, 0x8E);
    idt_SetGate(14, isr14, 0x8E);
    idt_SetGate(15, isr15, 0x8E);
    idt_SetGate(16, isr16, 0x8E);
    idt_SetGate(17, isr17, 0x8E);
    idt_SetGate(18, isr18, 0x8E);
    idt_SetGate(19, isr19, 0x8E);
    idt_SetGate(20, isr20, 0x8E);
    idt_SetGate(21, isr21, 0x8E);
    idt_SetGate(22, isr22, 0x8E);
    idt_SetGate(23, isr23, 0x8E);
    idt_SetGate(24, isr24, 0x8E);
    idt_SetGate(25, isr25, 0x8E);
    idt_SetGate(26, isr26, 0x8E);
    idt_SetGate(27, isr27, 0x8E);
    idt_SetGate(28, isr28, 0x8E);
    idt_SetGate(29, isr29, 0x8E);
    idt_SetGate(30, isr30, 0x8E);
    idt_SetGate(31, isr31, 0x8E);

    idt_ptr.limit = (sizeof(struct E_IDT_ENTRY) * 256) - 1;
    idt_ptr.base = (UINT64)&idt;

    __asm__ volatile("lidt %0" : : "m"(idt_ptr));
    __asm__ volatile("sti");
}