#ifndef BOOT_REGS_H
#define BOOT_REGS_H

struct registers {
    unsigned int ds;
    unsigned int ebp;
    unsigned int esi;
    unsigned int edi;
    unsigned int edx;
    unsigned int ecx;
    unsigned int ebx;
    unsigned int eax;
    unsigned int int_no;
    unsigned int int_err_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
    unsigned int esp;
    unsigned int ss;  
};

#endif