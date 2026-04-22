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
#include "lfb.h"
#include "driver.h"
#include "stdint.h"
#include <malloc.h>
#include <string.h>

static INT32 lfb_InitE(E_DRV* self)
{
    E_LFBDRV* lfb = (E_LFBDRV*)self;
    if (lfb->back_buffer != NULL) return 0;
    struct limine_framebuffer_request* req = self->private_data;

    if (!req->response || req->response->framebuffer_count < 1) return -1;

    struct limine_framebuffer* fb = req->response->framebuffers[0];
    lfb->address = fb->address;
    lfb->width = fb->width;
    lfb->height = fb->height;
    lfb->pitch = fb->pitch;

    SIZE buffer_size = (fb->pitch * fb->height) + 4096;
    lfb->back_buffer = (UINT32*)kMallocE(buffer_size);
    if (!lfb->back_buffer) {
        return -1;
    }
    MemSet(lfb->back_buffer, 0, buffer_size);
    return 0;
}

E_LFBDRV* lfb_CreateDrvE(struct limine_framebuffer_request* req)
{
    E_LFBDRV* lfb = (E_LFBDRV*)kMallocE(sizeof(E_LFBDRV));
    if (!lfb || !req->response || req->response->framebuffer_count < 1) {
        return NULL;
    }
    MemSet(lfb, 0, sizeof(E_LFBDRV));
    UUID4 target_id;
    uuid4_NewStr("be67439d-98cb-484b-8c71-fc5dbe809623", &target_id);
    lfb->base.name = "LFB Video";
    lfb->base.init = lfb_InitE;
    lfb->base.private_data = req;
    lfb->base.interface_id = target_id;
    lfb->base.instance_id = target_id;

    E_DRV_MEM_REGION* region = (E_DRV_MEM_REGION*)kMallocE(sizeof(E_DRV_MEM_REGION));
    if (region) {
        region->base = (UINTPTR)req->response->framebuffers[0]->address;
        region->size = req->response->framebuffers[0]->height * req->response->framebuffers[0]->pitch;
        region->flags = 0;
        region->next = NULL;
        lfb->base.mem_regions = region;
    }

    drv_RegE((E_DRV*)lfb);

    return lfb;
}

VOID lfb_SwapBuffersE(E_LFBDRV *lfb)
{
    if (!lfb || !lfb->back_buffer) return;
    MemCpy(lfb->address, lfb->back_buffer, lfb->pitch * lfb->height);
}

VOID lfb_DrawPointE(E_LFBDRV *lfb, UINT64 x, UINT64 y, UINT32 color)
{
    if (x >= lfb->width || y >= lfb->height) {
        return;
    }
    lfb->back_buffer[y * (lfb->pitch / 4) + x] = color;
}

VOID lfb_ClearScreenE(E_LFBDRV *lfb, UINT32 color)
{
    for (SIZE i = 0; i < lfb->pitch * lfb->height; i++) {
        lfb->back_buffer[i] = color;
    }
}