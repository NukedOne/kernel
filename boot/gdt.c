#include "gdt.h"

uint64_t gdt[] = {
    0x0000000000000000,
    0x00CF9A000000FFFF,
    0x00CF92000000FFFF,
    0x00CFFA000000FFFF,
    0x00CFF2000000FFFF,    
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
) {
    uint64_t gdte = 0;

    uint64_t lower_dw = (base_addr & 0x0000FFFF) << 16 | (segment_limit & 0x0FFFF);
    
    uint64_t higher_dw_left = (base_addr & 0xFF000000) << 8 | granularity << 7 | db << 6 | 0 << 5 | avl << 4 | segment_limit >> 16;
    uint64_t higher_dw_right = (present << 15) | (dpl << 13) | s << 12 | type << 8 | (base_addr & 0x00FF0000);

    uint64_t higher_dw = (higher_dw_left << 16) | higher_dw_right;

    gdte = (higher_dw << 32) | lower_dw; 

    return gdte;
}


