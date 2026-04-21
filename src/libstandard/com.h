#ifndef COM_H
#define COM_H
#pragma once

#include <stdint.h>
#include <stddef.h>

VOID com_SerialInitE();
INT32 com_IsTransmitEmptyE();
VOID com_PutCE(CHAR a);
VOID com_PrintE(const CHAR* s);
VOID com_PrintHexE(UINT64 val);

#endif