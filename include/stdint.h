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
#ifndef STDINT_H
#define STDINT_H
#pragma once

typedef __UINT8_TYPE__ UINT8;
typedef __UINT16_TYPE__ UINT16;
typedef __UINT32_TYPE__ UINT32;
typedef __UINT64_TYPE__ UINT64;

typedef __INT8_TYPE__ INT8;
typedef __INT16_TYPE__ INT16;
typedef __INT32_TYPE__ INT32;
typedef __INT64_TYPE__ INT64;

typedef __UINTPTR_TYPE__ UINTPTR;
typedef __INTPTR_TYPE__  INTPTR;

typedef __SIZE_TYPE__ SIZE;

#define UINT64_MAX       (__UINT64_C(18446744073709551615))
#define INT64_MAX        (__INT64_C(9223372036854775807))

#endif