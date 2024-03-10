#include <stdint.h>
#include "multiboot.h"
#include "gdt.h"
#include "idt.h"
#include "print.h"


void __attribute__((noreturn)) main(struct multiboot_info *mb) {
    printf("bootloader: init\n");

    gdt_load(sizeof(gdt) - 1, &gdt);
    printf("gdt: init\n");

    idt_init();
    printf("idt: init\n");

    asm (
        "sti"
    );

    asm (
        "hlt"
    );

}
