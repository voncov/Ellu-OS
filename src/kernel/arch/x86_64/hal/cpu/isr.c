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
#include <isr.h>
#include <stdint.h>
#include <string.h>
#include <com.h>

struct E_INTERRUPT_FRAME {
    UINT64 rax;
    UINT64 rbx;
    UINT64 rcx;
    UINT64 rdx;
    UINT64 rsi;
    UINT64 rdi;
    UINT64 rbp;
    UINT64 r8;
    UINT64 r9;
    UINT64 r10;
    UINT64 r11;
    UINT64 r12;
    UINT64 r13;
    UINT64 r14;
    UINT64 r15;
    UINT64 int_no;
    UINT64 err_code;
    UINT64 rip;
    UINT64 cs;
    UINT64 rflags;
    UINT64 rsp;
    UINT64 ss;
} __attribute__((packed));

E_LFBDRV *g_lfb;
E_TTYDRV *g_tty;

const CHAR *int_names[22] = {
    [0x00] = "DIVIDE_BY_ZERO",
    [0x01] = "DEBUG_EXCEPTION",
    [0x02] = "NMI_INT",
    [0x03] = "BREAKPOINT",
    [0x04] = "OVERFLOW",
    [0x05] = "BOUND_RANGE_EXC",
    [0x06] = "INVALID_OPCODE",
    [0x07] = "DEVICE_NOTAVAIL",
    [0x08] = "DOUBLE_FAULT",
    [0x09] = "COPROC_SRGORRUN",
    [0x0A] = "INVALID_TSS",
    [0x0B] = "SEG_NO_PRESENT",
    [0x0C] = "STACK_SEGFAULT",
    [0x0D] = "GEN_PROT_FAULT",
    [0x0E] = "INTEL_RESERVED",
    [0x0F] = "DIVIDE_BY_ZERO",
    [0x10] = "X87_FPU_FPE",
    [0x11] = "ALIGMENT_CHK",
    [0x12] = "MACHINE_CHR",
    [0x13] = "SIMD_FPE",
    [0x14] = "VIRT_EXC",
    [0x15] = "CONTROL_PROT_EXC",
};

VOID isr_Init(E_LFBDRV *lfb, E_TTYDRV *tty)
{
    g_lfb = lfb;
    g_tty = tty;
}

VOID isr_handler(struct E_INTERRUPT_FRAME *frame)
{
    UINT32 color = 0x1145ff;
    lfb_ClearScreenE(g_lfb, color);
    g_tty->cursor_x = 0;
    g_tty->cursor_y = 0;
    tty_SetBkgColorE(g_tty, color);
    CHAR buf[1024];
    snPrintF(buf, sizeof(buf), "{#FFFFFF}KERNEL ERROR.\n[INT_NAME]=\'%s\'\n[rbx]=0x%llx\n[rcx]=0x%llx\n[rdx]=0x%llx\n[rsi]=0x%llx\n[rdi]=0x%llx\n[rbp]=0x%llx\n[r8]=0x%llx\n[r9]=0x%llx\n[r10]=0x%llx\n[r11]=0x%llx\n[r12]=0x%llx\n[r13]=0x%llx\n[r14]=0x%llx\n[r15]=0x%llx\n\n[err_code]=0x%llx\n[rip]=0x%llx\n[cs]=0x%llx\n[rflags]=0x%llx\n[rsp]=0x%llx\n[ss]=0x%llx", int_names[frame->int_no], frame->rax, frame->rbx, frame->rcx, frame->rdx, frame->rsi, frame->rdi, frame->rbp, frame->r8, frame->r9, frame->r10, frame->r11, frame->r12, frame->r13, frame->r14, frame->r15, frame->rip, frame->cs, frame->rflags, frame->rsp, frame->ss);
    com_PrintE(buf);
    tty_WriteE(g_tty, buf);
    lfb_SwapBuffersE(g_lfb);
    __asm__("hlt");
    return;
}