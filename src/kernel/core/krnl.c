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
#include "krnl.h"
#include <pmm.h>
#include <logo.h>
#include <uuid4.h>
#include <limine.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <driver.h>
#include <tty/tty.h>
#include <video/lfb.h>
#include <com.h>
#include <gdt.h>

__attribute__((used, section(".limine_requests")))
struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 1
};

__attribute__((used, section(".limine_requests")))
struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

VOID krnl_Main(VOID)
{
    gdt_Init();
    com_SerialInitE();
    com_PrintE("ElluKernel boot up!\n");
    pmm_Init(&memmap_request);
    kMallocInitE(512);
    E_LFBDRV *lfb = lfb_CreateDrvE(&fb_request);
    krnl_DrawLogo(lfb);
    E_TTYDRV *tty = tty_CreateDrvE();
    if (tty) {
        tty->base.init((E_DRV*)tty);
        tty_WriteE(tty, "{#FFFFFF}ElluKernel v.0.1.1-alpha {#CCCCCC}(Build 51){#FFFFFF} - Ellu-OS Copyright (c) 2026 voncov\n");
        tty_WriteE(tty, "{#FFFFFF}  Official repo: {#3467EB}https://github.com/voncov/Ellu-OS{#FFFFFF}\n");
        CHAR lfb_memmap[256];
        snPrintF(lfb_memmap, sizeof(lfb_memmap), "{#34eb83}E_LFBDRV found:\n  {#21A4ab}Ptr: {#CCCCCC}0x%p\n  {#21A4ab}Addr: {#CCCCCC}0x%x\n", lfb, lfb->base.mem_regions->base);
        tty_WriteE(tty, lfb_memmap);
        CHAR tty_memmap[256];
        snPrintF(tty_memmap, sizeof(tty_memmap), "{#34eb83}E_TTYDRV found:\n  {#21A4ab}Ptr: {#CCCCCC}0x%p\n  {#21A4ab}Addr: {#CCCCCC}0x%x\n", tty, 0);
        tty_WriteE(tty, tty_memmap);
    }
    lfb_SwapBuffersE(lfb);
    for (;;);
}

VOID krnl_DrawLogo(E_LFBDRV *lfb)
{
    UINT32 x = (lfb->width - logo_width) / 2;
    UINT32 y = (lfb->height - logo_height) / 2;

    for (UINT32 ly = 0; ly < logo_height; ly++) {
        for (UINT32 lx = 0; lx < logo_width; lx++) {
            UINT32 color = logo_data[ly * logo_width + lx];
            if (color != 0x00000000) {
                UINT32 screen_x = x + lx;
                UINT32 screen_y = y + ly;
                lfb->back_buffer[screen_y * (lfb->pitch / 4) + screen_x] = color;
            }
        }
    }
}