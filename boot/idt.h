#ifndef BOOT_IDT_H
#define BOOT_IDT_H

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

#endif