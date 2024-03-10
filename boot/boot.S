.set MAGIC, 0x1BADB002
.set FLAGS, 0x3
.set CHECKSUM, -(MAGIC+FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .data
.align 8
gdtr:
    .word 0
    .long 0
idtr:
    .word 0
    .long 0


.section .text
.global start
start:
    cli

    movl $stack_top, %esp

    pushl %ebx
    call main
.size start, . - start

.global gdt_load
gdt_load:
    mov 4(%esp), %ax
    mov %ax, gdtr
    movl 8(%esp), %eax
    movl %eax, gdtr+2

    lgdt gdtr

    ljmp $0x08, $reload_segments

.global idt_flush
.type idt_flush, @function
idt_flush:
    mov 4(%esp), %esi
    mov 0(%esi), %eax
    mov %eax, idtr
    movl 2(%esi), %eax
    movl %eax, idtr+2

    lidt idtr

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
stack_bottom:
.skip 16384
stack_top:
