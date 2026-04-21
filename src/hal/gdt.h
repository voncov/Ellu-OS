#include <stdint.h>
#include <stddef.h>

struct E_GDT_ENTRY {
    UINT16 limit_low;
    UINT16 base_low;
    UINT8 base_middle;
    UINT8 access;
    UINT8 granularity;
    UINT8 base_high;
} __attribute__((packed));

struct E_GDT_PTR {
    UINT16 limit;
    UINT64 base;
} __attribute__((packed));

VOID gdt_SetEntry(INT32 num, UINT32 base, UINT32 limit, UINT8 access, UINT8 granularity);
VOID gdt_Init();