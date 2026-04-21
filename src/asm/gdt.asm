[BITS 64]
section .text
global gdt_Load

gdt_Load:
lgdt [rdi]

mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax

push 0x08
lea rax, [rel .reload_cs]
push rax
retfq

.reload_cs:
ret