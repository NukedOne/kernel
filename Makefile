all: boot.iso

CC = crossgcc

boot.iso: boot/boot.bin
	mkisofs \
		-o $@ -b boot/grub/stage2_eltorito \
		-r -no-emul-boot -boot-load-size 4 \
		-J -boot-info-table -graft-points \
		boot/boot.bin=boot/boot.bin \
		fs 

CSRC := $(wildcard boot/*.c)
ASMSRC := $(wildcard boot/*.S)

COBJ := $(CSRC:.c=.o)
ASMOBJ := $(ASMSRC:.S=.o)

CFLAGS := -fno-builtin -ffreestanding -no-pie -fno-pic -mgeneral-regs-only \
	  -mno-red-zone -O3 -W -Wall -z,max-page-size=4096 -nodefaultlibs  \
	  -ggdb -nostdlib

boot/boot.bin: $(COBJ) $(ASMOBJ)
	ld $(COBJ) $(ASMOBJ) -melf_i386 -T boot/linker.ld -o $@

boot/%.o: boot/%.c
	$(CC) -c $^ -o $@ -m32 $(CFLAGS)

boot/%.o: boot/%.S
	$(CC) -c $^ -o $@ -m32

clean:
	$(RM) boot.iso boot/boot.bin boot/*.o