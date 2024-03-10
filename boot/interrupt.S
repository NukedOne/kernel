.section .data
gen:
    .string "generic called\n"

.global generic_isr
.type generic_isr, @function
generic_isr:
    cli
    push $gen
    call printf
    iretl
.size generic_isr, . - generic_isr

