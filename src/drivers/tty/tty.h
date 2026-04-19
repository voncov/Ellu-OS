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
#ifndef TTY_H
#define TTY_H
#pragma once

#include <driver.h>
#include <video/lfb.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    E_DRV base;
    E_LFBDRV* vdev;
    UINT32 fg_color;
    UINT32 bg_color;
    UINT64 cursor_x;
    UINT64 cursor_y;
} E_TTYDRV;

E_TTYDRV* tty_CreateDrvE();
VOID tty_PutCE(E_TTYDRV* tty, CHAR c);
VOID tty_WriteE(E_TTYDRV* tty, const CHAR* str);

#endif