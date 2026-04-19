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
#ifndef STRING_H
#define STRING_H
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

INT32 StrCmp(const CHAR *s1, const CHAR *s2);
SIZE StrLen(const CHAR *s);
VOID *MemSet(VOID *s, INT32 c, SIZE n);
VOID *MemCpy(VOID *dest, const VOID *src, SIZE n);
INT32 vsnPrintF(CHAR *str, SIZE size, const CHAR *format, VA_LIST ap);
INT32 snPrintF(CHAR *str, SIZE size, const CHAR *format, ...);
INT32 sPrintF(CHAR *str, const CHAR *format, ...);

#endif