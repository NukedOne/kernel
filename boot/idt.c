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
    int i;
    for (i = 0; i < 256; i++)
        idt_reserve_vector(i, generic_isr);

    idt_load(sizeof(idt_entries) - 1, &idt_entries);
}

void idt_load(uint16_t limit, uintptr_t base) {
    idt_ptr.base = (uintptr_t)base;
    idt_ptr.limit = limit;

    idt_flush((uintptr_t)&idt_ptr);
}
