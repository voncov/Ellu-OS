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
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

static CHAR* LongToStr(CHAR* str, UINT64 num, INT32 base)
{
    CHAR* ptr = str;
    CHAR* ptr1 = str;
    CHAR tmp_char;

    if (num == 0) {
        *ptr++ = '0';
        *ptr = '\0';
        return str;
    }
    
    while (num > 0) {
        UINT64 next_num = num / base;
        UINT64 digit = num % base;
        *ptr++ = "0123456789abcdef"[digit];
        num = next_num;
    }

    *ptr-- = '\0';

    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return str;
}

INT32 StrCmp(const CHAR *s1, const CHAR *s2)
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(UINT8*)s1 - *(UINT8*)s2;
}

SIZE StrLen(const CHAR *s)
{
    SIZE len = 0;
    while (s[len]) len++;
    return len;
}

VOID *MemSet(VOID *s, INT32 c, SIZE n)
{
    UINT8 *p = s;
    while (n--) *p++ = (UINT8)c;
    return s;
}

VOID *MemCpy(VOID *dest, const VOID *src, SIZE n)
{
    UINT8 *d = dest;
    const UINT8 *s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

INT32 vsnPrintF(CHAR *str, SIZE size, const CHAR *format, VA_LIST ap)
{
    SIZE written = 0;
    const CHAR *f = format;

    while (*f && written < size - 1) {
        if (*f == '%') {
            f++;
            INT32 isll = 0;
            INT32 isl = 0;
            while (*f == 'l') {
                if (isl) {
                    isll = 1;
                    isl = 0;
                } else {
                    isl = 1;
                }
                f++;
            }
            if (*f == 's') {
                const CHAR *s = va_Arg(ap, const CHAR*);
                if (!s) {
                    s = "(null)";
                }
                while (*s && written < size - 1) str[written++] = *s++;
            } 
            else if (*f == 'd' || *f == 'i') {
                CHAR buf[32];
                INT64 val = (isll || isl) ? va_Arg(ap, INT64) : (INT64)va_Arg(ap, INT32);
                LongToStr(buf, val, 10);
                CHAR *p = buf;
                while (*p && written < size - 1) str[written++] = *p++;
            }
            else if (*f == 'x' || *f == 'p') {
                CHAR buf[32];
                UINT64 val = (isll || isl || *f == 'p') ? va_Arg(ap, UINT64) : (UINT64)va_Arg(ap, UINT32);
                LongToStr(buf, val, 16);
                CHAR *p = buf;
                while (*p && written < size - 1) str[written++] = *p++;
            }
            else if (*f == 'c') {
                str[written++] = (CHAR)va_Arg(ap, INT32);
            }
            else if (*f == '%') {
                str[written++] = '%';
            }
        } else {
            str[written++] = *f;
        }        
        f++;
    }

    str[written] = '\0';
    return (INT32)written;
}

INT32 snPrintF(CHAR *str, SIZE size, const CHAR *format, ...)
{
    VA_LIST ap;
    va_Start(ap, format);
    INT32 result = vsnPrintF(str, size, format, ap);
    va_End(ap);
    return result;
}

INT32 sPrintF(CHAR *str, const CHAR *format, ...)
{
    VA_LIST ap;
    va_Start(ap, format);
    INT32 result = vsnPrintF(str, (SIZE)-1, format, ap);
    va_End(ap);
    return result;
}