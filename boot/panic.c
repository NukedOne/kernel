#include "panic.h"
#include "print.h"

void __attribute__((noreturn)) panic(const char *msg)
{
    printf("kernel panic: %s\n", msg);

    for (;;)
    {
        asm ("hlt");
    }
}