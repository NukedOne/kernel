.set MAGIC, 0x1BADB002
.set FLAGS, 0x3
.set CHECKSUM, -(MAGIC+FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global start
start:
    cli

    movl $stack_top, %esp

    pushl %ebx
    call boot_main
.size start, . - start

.global gdt_flush
gdt_flush:
    lgdt gdt_ptr
    ljmp $0x08, $reload_segments

.global idt_flush
.type idt_flush, @function
idt_flush:
    lidt idt_ptr
    ret
.size idt_flush, . - idt_flush


reload_segments:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    ret

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:
