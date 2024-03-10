#include "print.h"
#include <stdarg.h>
#include <stdint.h>

unsigned char *VIDEO_MEM = 0xB8000;
unsigned int ROW = 0, COLUMN = 0;
unsigned int WIDTH = 80, HEIGHT = 24;
unsigned int CURRENT_SCREENFUL = 0;


void memcpy(void *dst, void *src, int n) {
    char *d = dst, *s = src;
    while (n--)
        *d++ = *s++;
}

int strlen(const char *s) {
    int len = 0;
    while (*s++)
        len++;
    return len;
}

void putchar(char c) {
    uint16_t vga_char = (0x7f << 8) | c;
    memcpy(VIDEO_MEM + (WIDTH*HEIGHT*2*CURRENT_SCREENFUL) + ((ROW*WIDTH) + COLUMN)*2, &vga_char, sizeof(vga_char));

    COLUMN++;

    if (COLUMN >= WIDTH) {
        ROW++;
        COLUMN = 0;
    }

    if (ROW >= HEIGHT) {
        ROW = 0;
        CURRENT_SCREENFUL++;
    }
}

void print_int(int n) {
    char buf[20] = {0};

    int i = 0;

    if (n == 0) putchar('0');

    while (n > 0) {
        buf[i] = (n % 10) + '0';
        n /= 10;
        i++;
    }

    while (i--) {
        putchar(buf[i]);
    }

}

void print_string(const char *s) {
    int i;
    for (i = 0; i < strlen(s); i++)
        putchar(s[i]);
}

void printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int i;
    for (i = 0; i < strlen(fmt); i++) {
        if (fmt[i] == '%') {
            i++;

            switch (fmt[i]) {
            case 'd': {
                int arg = va_arg(ap, int);
                print_int(arg);
                break;
            }
            case 's': {
                char *arg = va_arg(ap, char *);
                print_string(arg);
                break;
            }
            default:
                break;
            }

            continue;
        }

        if (fmt[i] == '\n') {
            ROW++;
            COLUMN = 0;

            if (ROW >= HEIGHT)
                CURRENT_SCREENFUL++;

            continue;
        }

        putchar(fmt[i]);
    }

    va_end(ap);
}
