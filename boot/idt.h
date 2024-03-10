#ifndef BOOT_IDT_H
#define BOOT_IDT_H

#include "regs.h"

#define TOTAL_INTERRUPTS 256

#include <stdint.h>

struct idt_entry {
    uint16_t target_cs_offset_low;
    uint16_t target_cs_selector;
    uint8_t zero;
    uint8_t flags_and_type;
    uint16_t target_cs_offset_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed));

void idt_load(uint16_t limit, uintptr_t base);
void idt_init();
void idt_flush(uintptr_t idt_ptr);

void generic_isr(const char *s);

void dispatch_interrupt(struct registers *regs);

void isr0(void);
void isr1(void);
void isr2(void);
void isr3(void);
void isr4(void);
void isr5(void);
void isr6(void);
void isr7(void);
void isr8(void);
void isr9(void);
void isr10(void);
void isr11(void);
void isr12(void);
void isr13(void);
void isr14(void);
void isr15(void);
void isr16(void);
void isr17(void);
void isr18(void);
void isr19(void);
void isr20(void);
void isr21(void);
void isr22(void);
void isr23(void);
void isr24(void);
void isr25(void);
void isr26(void);
void isr27(void);
void isr28(void);
void isr29(void);
void isr30(void);
void isr31(void);

#endif