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

void isr_division_error(struct registers *regs);
void isr_debug(struct registers *regs);
void isr_non_maskable_interrupt(struct registers *regs);
void isr_breakpoint(struct registers *regs);
void isr_overflow(struct registers *regs);
void isr_bound_range_exceeded(struct registers *regs);
void isr_invalid_opcode(struct registers *regs);
void isr_device_not_available(struct registers *regs);
void isr_double_fault(struct registers *regs);
void isr_coprocessor_segment_overrun(struct registers *regs);
void isr_invalid_tss(struct registers *regs);
void isr_segment_not_present(struct registers *regs);
void isr_stack_segment_fault(struct registers *regs);
void isr_general_protection_fault(struct registers *regs);
void isr_page_fault(struct registers *regs);
void isr_x87_floating_point_exception(struct registers *regs);
void isr_alignment_check(struct registers *regs);
void isr_machine_check(struct registers *regs);
void isr_simd_floating_point_exception(struct registers *regs);
void isr_virtualization_exception(struct registers *regs);
void isr_control_protection_exception(struct registers *regs);
void isr_hypervisor_injection_exception(struct registers *regs);
void isr_vmm_communication_exception(struct registers *regs);
void isr_security_exception(struct registers *regs);
void isr_triple_fault(struct registers *regs);
void isr_fpu_error_interrupt(struct registers *regs);

void isr_dummy(struct registers *regs);

#endif