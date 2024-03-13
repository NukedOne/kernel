#ifndef BOOT_GDT_H
#define BOOT_GDT_H

#include <stdint.h>

struct gdt_entry {
    uint64_t limit_low :16;
    uint64_t base_low :16;
    uint64_t base_middle :8;
    uint64_t type :4;
    uint64_t s :1;
    uint64_t dpl :2;
    uint64_t present :1;
    uint64_t limit_high :4;
    uint64_t reserved :1;
    uint64_t avl :1;
    uint64_t db :1;
    uint64_t granularity :1;
    uint64_t base_high :8;
};

static uint64_t make_gdt_entry(
    uint64_t base_addr,
    uint64_t segment_limit,
    uint64_t type,
    uint64_t s,
    uint64_t dpl,
    uint64_t present,
    uint64_t avl,
    uint64_t db,
    uint64_t granularity
);

void gdt_flush();
void gdt_init();

extern uint64_t gdt[5];

#endif