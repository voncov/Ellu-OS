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
#include <stddef.h>
#include <limine.h>
#include <font.h>
#include <background.h>

extern struct limine_framebuffer_request fb_request;

static uint64_t cursor_x = 0;
static uint64_t cursor_y = 0;

static uint32_t hex_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

void put_pixel(uint64_t x, uint64_t y, uint32_t color) {
    struct limine_framebuffer *fb = fb_request.response->framebuffers[0];
    uint32_t *fb_ptr = fb->address;
    fb_ptr[y * (fb->pitch / 4) + x] = color;
}

void draw_image_centered() {
    struct limine_framebuffer *fb = fb_request.response->framebuffers[0];
    
    uint32_t start_x = (fb->width - IMG_WIDTH) / 2;
    uint32_t start_y = (fb->height - IMG_HEIGHT) / 2;

    for (uint32_t y = 0; y < IMG_HEIGHT; y++) {
        for (uint32_t x = 0; x < IMG_WIDTH; x++) {
            uint32_t color = image_data[y * IMG_WIDTH + x];            
            put_pixel(start_x + x, start_y + y, color);
        }
    }
}

void kputchar(char c, uint32_t color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y += 16;
        return;
    }

    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 8; col++) {
            if ((font8x16[(unsigned char)c][row] >> (7 - col)) & 1) {
                put_pixel(cursor_x + col, cursor_y + row, color);
            }
        }
    }
    cursor_x += 8;
}

void kprint(const char *str, uint32_t default_color) {
    uint32_t current_color = default_color;

    while (*str) {
        if (*str == '{') {
            const char *ptr = str + 1;
            uint32_t new_color = 0;
            int is_tag = 1;

            for (int i = 0; i < 6; i++) {
                if (ptr[i] == '\0' || ptr[i] == '}') {
                    is_tag = 0;
                    break;
                }
                new_color = (new_color << 4) | hex_to_int(ptr[i]);
            }

            if (is_tag && ptr[6] == '}') {
                current_color = new_color;
                str = ptr + 7;
                continue;
            }
        }

        kputchar(*str++, current_color);
    }
}