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
#include "tty.h"
#include <font.h>
#include <uuid4.h>

static E_TTYDRV global_tty;

static VOID tty_DrawPixelE(E_TTYDRV* tty, UINT64 x, UINT64 y, UINT32 color)
{
    if (x >= tty->vdev->width || y >= tty->vdev->height) {
        return;
    }
    UINT32* fb_ptr = tty->vdev->address;
    fb_ptr[y * (tty->vdev->pitch / 4) + x] = color;
}

static INT32 hexToInt(CHAR c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return 0;
}

static INT32 tty_InitE(E_DRV* self)
{
    E_TTYDRV* tty = (E_TTYDRV*)self;
    E_DRV* vdrv = drv_UuidFindE(uuid4_NewStr("be67439d-98cb-484b-8c71-fc5dbe809623"));
    
    if (vdrv == NULL) {
        return -1;
    }
    tty->vdev = (E_LFBDRV*)vdrv;
    
    tty->cursor_x = 0;
    tty->cursor_y = 0;
    
    return 0;
}

INT32 tty_SetupE()
{
    global_tty.base.name = "System TTY";
    global_tty.base.interface_id = uuid4_NewStr("607a2963-82ad-4c39-a6b1-58f6f30ec33b");
    global_tty.base.instance_id = uuid4_NewStr("607a2963-82ad-4c39-a6b1-58f6f30ec33b");
    global_tty.base.init = tty_InitE;
    global_tty.fg_color = 0xFFFFFF;
    global_tty.bg_color = 0x000000;

    return drv_RegE((E_DRV*)&global_tty);
}

VOID tty_PutCE(E_TTYDRV* tty, CHAR c)
{
    if (c == '\n') {
        tty->cursor_x = 0;
        tty->cursor_y += 16;
        return;
    }

    if (tty->cursor_y + 16 > tty->vdev->height) {
        tty->cursor_y = 0; 
    }

    for (INT32 row = 0; row < 16; row++) {
        for (INT32 col = 0; col < 8; col++) {
            UINT32 color = (font8x16[(UINT16)c][row] >> (7 - col)) & 1 ? tty->fg_color : tty->bg_color;
            tty_DrawPixelE(tty, tty->cursor_x + col, tty->cursor_y + row, color);
        }
    }
    tty->cursor_x += 8;
    if (tty->cursor_x + 8 > tty->vdev->width) {
        tty_PutCE(tty, '\n');
    }
}

VOID tty_WriteE(E_TTYDRV* tty, const CHAR* str)
{
    while (*str) {
        if (str[0] == '{' && str[1] == '#') {
            const CHAR* ptr = str + 2;
            UINT32 new_color = 0;
            INT32 is_tag = 1;
            for (INT32 i = 0; i < 6; i++) {
                if (ptr[i] == '\0' || ptr[i] == '}') {
                    is_tag = 0;
                    break;
                }
                new_color = (new_color << 4) | hexToInt(ptr[i]);
            }
            if (is_tag && ptr[6] == '}') {
                tty->fg_color = new_color;
                str = ptr + 7;
                continue;
            }
        }
        tty_PutCE(tty, *str++);
    }
}