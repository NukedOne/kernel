#include "idt.h"
#include "print.h"

#define FLAG_TYPE_SHIFT 0
#define FLAG_DPL_SHIFT 5
#define FLAG_PRESENT 128

struct idt_ptr idt_ptr = {0};
struct idt_entry idt_entries[TOTAL_INTERRUPTS] = {0};

void idt_create_descriptor(uint8_t index, uint32_t offset, uint16_t selector, uint8_t flags) {
    idt_entries[index].target_cs_offset_low = offset & 0xFFFF;
    idt_entries[index].target_cs_offset_high = (offset >> 16) & 0xFFFF;
    idt_entries[index].target_cs_selector = selector;
    idt_entries[index].zero = 0;
    idt_entries[index].flags_and_type = flags;
}

void idt_reserve_vector(uint8_t index, void (*handler)()) {
    idt_create_descriptor(index, (uintptr_t)handler, 0x08, 0x8E);
}

void idt_init() {
    idt_reserve_vector(0, isr0);
    idt_reserve_vector(1, isr1);
    idt_reserve_vector(2, isr2);
    idt_reserve_vector(3, isr3);
    idt_reserve_vector(4, isr4);
    idt_reserve_vector(5, isr5);
    idt_reserve_vector(6, isr6);
    idt_reserve_vector(7, isr7);
    idt_reserve_vector(8, isr8);
    idt_reserve_vector(9, isr9);
    idt_reserve_vector(10, isr10);
    idt_reserve_vector(11, isr11);
    idt_reserve_vector(12, isr12);
    idt_reserve_vector(13, isr13);
    idt_reserve_vector(14, isr14);
    idt_reserve_vector(15, isr15);
    idt_reserve_vector(16, isr16);
    idt_reserve_vector(17, isr17);
    idt_reserve_vector(18, isr18);
    idt_reserve_vector(19, isr19);
    idt_reserve_vector(20, isr20);
    idt_reserve_vector(21, isr21);
    idt_reserve_vector(22, isr22);
    idt_reserve_vector(23, isr23);
    idt_reserve_vector(24, isr24);
    idt_reserve_vector(25, isr25);
    idt_reserve_vector(26, isr26);
    idt_reserve_vector(27, isr27);
    idt_reserve_vector(28, isr28);
    idt_reserve_vector(29, isr29);
    idt_reserve_vector(30, isr30);
    idt_reserve_vector(31, isr31);

    idt_load(sizeof(idt_entries) - 1, &idt_entries);
}

void idt_load(uint16_t limit, uintptr_t base) {
    idt_ptr.base = (uintptr_t)base;
    idt_ptr.limit = limit;

    idt_flush((uintptr_t)&idt_ptr);
}
