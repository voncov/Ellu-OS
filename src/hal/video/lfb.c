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

static E_LFBDRV global_lfb;

static INT32 lfb_InitE(E_DRV* self)
{
    E_LFBDRV* lfb = (E_LFBDRV*)self;
    struct limine_framebuffer_request* req = self->private_data;

    if (!req->response || req->response->framebuffer_count < 1) return -1;

    struct limine_framebuffer* fb = req->response->framebuffers[0];
    lfb->address = fb->address;
    lfb->width = fb->width;
    lfb->height = fb->height;
    lfb->pitch = fb->pitch;
    return 0;
}

E_LFBDRV* lfb_CreateDrvE(struct limine_framebuffer_request* req)
{
    global_lfb.base.name = "LFB Video";
    global_lfb.base.interface_id = uuid4_NewStr("be67439d-98cb-484b-8c71-fc5dbe809623");
    global_lfb.base.instance_id = uuid4_NewStr("be67439d-98cb-484b-8c71-fc5dbe809623");
    global_lfb.base.init = lfb_InitE;
    global_lfb.base.private_data = req;

    if (drv_RegE((E_DRV*)&global_lfb) == 0) return &global_lfb;
    return NULL;
}