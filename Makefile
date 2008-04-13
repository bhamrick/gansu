CCFLAGS=-g -I. -fno-builtin -nostdinc
ASMFLAGS=-felf -g
LDFLAGS=-melf_i386
LINKER=linker.ld

all: kernel

kernel:
	nasm $(ASMFLAGS) -o build/boot.o src/boot.asm
	nasm $(ASMFLAGS) -o build/screen.o src/screen.asm
	nasm $(ASMFLAGS) -o build/gdt.o src/gdt.asm
	nasm $(ASMFLAGS) -o build/idt.o src/idt.asm
	nasm $(ASMFLAGS) -o build/memory.o src/memory.asm
	ld $(LDFLAGS) -o build/kernel build/boot.o build/screen.o build/gdt.o build/idt.o build/memory.o -T$(LINKER)
	cp build/kernel iso/boot/kernel
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o grub.iso iso

clean: 
	rm build/*
	rm grub.iso
