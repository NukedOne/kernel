#include <stdint.h>
#include "multiboot.h"
#include "gdt.h"
#include "idt.h"
#include "print.h"

void __attribute__((noreturn)) boot_main(struct multiboot_info *mb)
{
    printf("bootloader: init\n");

    gdt_init();
    printf("gdt: init\n");

    idt_init();
    printf("idt: init\n");

    printf("spam: %d\n", 1/0);
}
