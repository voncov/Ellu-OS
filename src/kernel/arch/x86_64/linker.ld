OUTPUT_FORMAT(elf64-x86-64)
ENTRY(krnl_Main)

SECTIONS
{
    . = 0xffffffff80000000;

    .text : {
        *(.text .text.*)
    }

    .rodata : {
        *(.rodata .rodata.*)
    }

    .data : {
        *(.data .data.*)
    }

    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    }
}