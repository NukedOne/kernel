ENTRY(start)
OUTPUT_FORMAT("elf32-i386")

SECTIONS {
    . = 0x100000;

    .text : {
        *(.multiboot)
        *(.text)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : ALIGN(8) { *(.data); }

    .bss : {
        *(.bss)
    }
}