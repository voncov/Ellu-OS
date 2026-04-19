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
#include "driver.h"
#include <string.h>

#define MAX_DRIVERS 512

static E_DRV* driver_registry[MAX_DRIVERS];
static UINT32 driver_count = 0;

INT32 drv_RegE(E_DRV* drv)
{
    if (driver_count >= MAX_DRIVERS || drv == NULL) {
        return -1;
    }

    if (drv->init && drv->init(drv) != 0) {
        return -2;
    }

    driver_registry[driver_count++] = drv;
    return 0;
}

E_DRV* drv_UuidFindE(UUID4 id)
{
    for (UINT32 i = 0; i < driver_count; i++) {
        if (uuid4_Equals(driver_registry[i]->interface_id, id)) {
            return driver_registry[i];
        }
    }
    return NULL;
}

E_DRV* drv_NameFindE(const CHAR* name)
{
    for (UINT32 i = 0; i < driver_count; i++) {
        if (StrCmp(driver_registry[i]->name, name) == 0) {
            return driver_registry[i];
        }
    }
    return NULL;
}