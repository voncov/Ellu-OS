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
#include <pmm.h>
#include <string.h>

static UINT8* bitmap;
static SIZE last_page_index = 0;
static SIZE total_pages = 0;

#define SET_BIT(i) (bitmap[i / 8] |= (1 << (i % 8)))
#define CLR_BIT(i) (bitmap[i / 8] &= ~(1 << (i % 8)))
#define GET_BIT(i) (bitmap[i / 8] & (1 << (i % 8)))

VOID pmm_Init(struct limine_memmap_request* memmap_req)
{
    struct limine_memmap_response* map = memmap_req->response;
    UINT64 max_addr = 0;
    for (SIZE i = 0; i < map->entry_count; i++) {
        struct limine_memmap_entry* entry = map->entries[i];
        if (entry->type == LIMINE_MEMMAP_USABLE) {
            max_addr = entry->base + entry->length;
        }
    }
    total_pages = max_addr / 4096;
    SIZE bitmap_size = total_pages / 8;
    for (SIZE i = 0; i < map->entry_count; i++) {
        struct limine_memmap_entry* entry = map->entries[i];
        if (entry->type == LIMINE_MEMMAP_USABLE && entry->length >= bitmap_size) {
            bitmap = (UINT8*)(entry->base + 0xFFFF800000000000);
            MemSet(bitmap, 0xFF, bitmap_size);
            entry->base += bitmap_size;
            entry->length -= bitmap_size;
            break;
        }
    }
    for (SIZE i = 0; i < map->entry_count; i++) {
        struct limine_memmap_entry* entry = map->entries[i];
        if (entry->type == LIMINE_MEMMAP_USABLE) {
            for (UINT64 addr = entry->base; addr < entry->base + entry->length; addr += 4096) {
                CLR_BIT(addr / 4096);
            }
        }
    }
}

VOID* pmm_AllocPage()
{
    for (SIZE i = last_page_index; i < total_pages; i++) {
        if (!GET_BIT(i)) {
            SET_BIT(i);
            last_page_index = i;
            return (VOID*)(i * 4096);
        }
    }
    return NULL;
}

VOID pmm_FreePage(VOID* addr)
{
    SIZE index = (UINT64)addr / 4096;
    CLR_BIT(index);
    if (index < last_page_index) last_page_index = index;
}