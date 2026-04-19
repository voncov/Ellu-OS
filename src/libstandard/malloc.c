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
#include "malloc.h"
#include <pmm.h>

typedef struct MHEADER {
    SIZE size;
    INT32 is_free;
    struct MHEADER *next;
} E_MHEADER;

static E_MHEADER *heap_start = NULL;

VOID kMallocInitE(SIZE initial_pages)
{
    for (SIZE i = 0; i < initial_pages; i++) {
        VOID* p = pmm_AllocPage();
        if (i == 0) {
            heap_start = (E_MHEADER*)((UINT64)p + HHDM_OFFSET);
            heap_start->size = (initial_pages * 4096) - sizeof(E_MHEADER);
            heap_start->is_free = 1;
            heap_start->next = NULL;
        }
    }
}

VOID *kMallocE(SIZE size)
{
    E_MHEADER *current = heap_start;
    while (current) {
        if (current->is_free && current->size >= size) {
            if (current->size > size + sizeof(E_MHEADER) + 16) {
                E_MHEADER *next_block = (E_MHEADER*)((UINT8*)current + sizeof(E_MHEADER) + size);
                next_block->size = current->size - size - sizeof(E_MHEADER);
                next_block->is_free = 1;
                next_block->next = current->next;

                current->size = size;
                current->next = next_block;
            }
            current->is_free = 0;
            return (VOID*)((UINT8*)current + sizeof(E_MHEADER));
        }
        current = current->next;
    }
    return NULL;
}

VOID kFreeE(VOID *ptr)
{
    if (!ptr) return;
    E_MHEADER *header = (E_MHEADER*)((UINT8*)ptr - sizeof(E_MHEADER));
    header->is_free = 1;
    E_MHEADER *current = heap_start;
    while (current && current->next) {
        if (current->is_free && current->next->is_free) {
            current->size += current->next->size + sizeof(E_MHEADER);
            current->next = current->next->next;
        }
        current = current->next;
    }
}