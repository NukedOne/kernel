#include "idt.h"
#include "print.h"
#include "panic.h"

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

void (*isr_table[])(struct registers *) = {
    isr_division_error,
    isr_debug,
    isr_non_maskable_interrupt,
    isr_breakpoint,
    isr_overflow,
    isr_bound_range_exceeded,
    isr_invalid_opcode,
    isr_device_not_available,
    isr_double_fault,
    isr_coprocessor_segment_overrun,
    isr_invalid_tss,
    isr_segment_not_present,
    isr_stack_segment_fault,
    isr_general_protection_fault,
    isr_page_fault,
    isr_dummy,
    isr_x87_floating_point_exception,
    isr_alignment_check,
    isr_machine_check,
    isr_simd_floating_point_exception,
    isr_virtualization_exception,
    isr_control_protection_exception,
    isr_dummy,
    isr_hypervisor_injection_exception,
    isr_vmm_communication_exception,
    isr_security_exception,
    isr_dummy,
    isr_triple_fault,
    isr_fpu_error_interrupt,
};

char (*exception_names[]) = {
    "division_error",
    "debug",
    "non_maskable_interrupt",
    "breakpoint",
    "overflow",
    "bound_range_exceeded",
    "invalid_opcode",
    "device_not_available",
    "double_fault",
    "coprocessor_segment_overrun",
    "invalid_tss",
    "segment_not_present",
    "stack_segment_fault",
    "general_protection_fault",
    "page_fault",
    "dummy",
    "x87_floating_point_exception",
    "alignment_check",
    "machine_check",
    "simd_floating_point_exception",
    "virtualization_exception",
    "control_protection_exception",
    "dummy",
    "hypervisor_injection_exception",
    "vmm_communication_exception",
    "security_exception",
    "dummy",
    "triple_fault",
    "fpu_error_interrupt",
};

void isr_division_error(struct registers *regs) { return; };
void isr_debug(struct registers *regs) { return; };
void isr_non_maskable_interrupt(struct registers *regs) { return; };
void isr_breakpoint(struct registers *regs) { return; };
void isr_overflow(struct registers *regs) { return; };
void isr_bound_range_exceeded(struct registers *regs) { return; };
// void isr_invalid_opcode(struct registers *regs) { return; };
void isr_device_not_available(struct registers *regs) { return; };
void isr_double_fault(struct registers *regs) { return; };
void isr_coprocessor_segment_overrun(struct registers *regs) { return; };
void isr_invalid_tss(struct registers *regs) { return; };
void isr_segment_not_present(struct registers *regs) { return; };
void isr_stack_segment_fault(struct registers *regs) { return; };
void isr_general_protection_fault(struct registers *regs) { return; };
void isr_page_fault(struct registers *regs) { return; };
void isr_x87_floating_point_exception(struct registers *regs) { return; };
void isr_alignment_check(struct registers *regs) { return; };
void isr_machine_check(struct registers *regs) { return; };
void isr_simd_floating_point_exception(struct registers *regs) { return; };
void isr_virtualization_exception(struct registers *regs) { return; };
void isr_control_protection_exception(struct registers *regs) { return; };
void isr_hypervisor_injection_exception(struct registers *regs) { return; };
void isr_vmm_communication_exception(struct registers *regs) { return; };
void isr_security_exception(struct registers *regs) { return; };
void isr_triple_fault(struct registers *regs) { return; };
void isr_fpu_error_interrupt(struct registers *regs) { return; };

void isr_dummy(struct registers *regs) { return; };

void isr_invalid_opcode(struct registers *regs) {
    panic(exception_names[regs->int_no]);
}

void dispatch_interrupt(struct registers *regs) {
    isr_table[regs->int_no](regs);
}