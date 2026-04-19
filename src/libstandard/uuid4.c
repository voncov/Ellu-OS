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
#include "stdint.h"
#include <uuid4.h>

static UINT8 hexToByte(const CHAR *s)
{
    UINT8 result = 0;
    for (INT32 i = 0; i < 2; i++) {
        CHAR c = s[i];
        result <<= 4;
        if (c >= '0' && c <= '9') {
            result |= (c - '0');
        }
        else if (c >= 'a' && c <= 'f') {
            result |= (c - 'a' + 10);
        }
        else if (c >= 'A' && c <= 'F') {
            result |= (c - 'A' + 10);
        }
    }
    return result;
}

INT32 uuid4_Equals(UUID4 a, UUID4 b)
{
    return (a.low == b.low) && (a.high == b.high);
}

UUID4 uuid4_NewFrom(UINT64 low, UINT64 high)
{
    UUID4 u = {
        .low = low,
        .high = high
    };
    return u;
}

VOID uuid4_NewStr(const CHAR *str, UUID4 *out)
{
    UINT8 bytes[16];
    INT32 byte_idx = 0;

    for (INT32 i = 0; i < 36 && byte_idx < 16; ) {
        if (str[i] == '-') {
            i++;
            continue;
        }
        bytes[byte_idx++] = hexToByte(&str[i]);
        i += 2;
    }

    out->high = 0;
    out->low = 0;
    for (INT32 i = 0; i < 8; i++) {
        out->high = (out->high << 8) | bytes[i];
        out->low  = (out->low << 8) | bytes[i + 8];
    }
}

VOID uuid4_ToStr(UUID4 uuid, CHAR *out)
{
    const CHAR *hex = "0123456789abcdef";
    INT32 pos = 0;
    for (INT32 i = 0; i < 16; i++) {
        if (i == 4 || i == 6 || i == 8 || i == 10) {
            out[pos++] = '-';
        }
        UINT8 val;
        if (i < 8) {
            val = (uuid.high >> ((7 - i) * 8)) & 0xFF;
        }
        else {
            val = (uuid.low  >> ((15 - i) * 8)) & 0xFF;
        }
        out[pos++] = hex[val >> 4];
        out[pos++] = hex[val & 0x0F];
    }
    out[pos] = '\0';
}