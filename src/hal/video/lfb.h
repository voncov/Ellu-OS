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
#ifndef LFB_H
#define LFB_H
#pragma once

#include <driver.h>
#include <limine.h>
#include <stdint.h>

typedef struct {
    E_DRV base;
    UINT32 *address;
    UINT32 *back_buffer;
    UINT32 width;
    UINT32 height;
    UINT32 pitch;
} E_LFBDRV;

E_LFBDRV* lfb_CreateDrvE(struct limine_framebuffer_request *req);
VOID lfb_SwapBuffersE(E_LFBDRV *lfb);
VOID lfb_DrawPointE(E_LFBDRV *lfb, UINT64 x, UINT64 y, UINT32 color);
VOID lfb_ClearScreenE(E_LFBDRV *lfb, UINT32 color);

#endif