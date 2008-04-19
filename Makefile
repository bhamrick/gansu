CCFLAGS=-g -I. -fno-builtin -nostdinc
ASMFLAGS=-felf -g
LDFLAGS=-melf_i386
LINKER=linker.ld

all: kernel
	echo done

kernel: src/boot.asm src/screen.asm src/gdt.asm src/idt.asm src/memory.asm src/pit.asm
	nasm $(ASMFLAGS) -o build/boot.o src/boot.asm
	nasm $(ASMFLAGS) -o build/screen.o src/screen.asm
	nasm $(ASMFLAGS) -o build/gdt.o src/gdt.asm
	nasm $(ASMFLAGS) -o build/idt.o src/idt.asm
	nasm $(ASMFLAGS) -o build/memory.o src/memory.asm
	nasm $(ASMFLAGS) -o build/pit.o src/pit.asm
	ld $(LDFLAGS) -o build/kernel build/boot.o build/screen.o build/gdt.o build/idt.o build/memory.o build/pit.o -T$(LINKER)
	cp build/kernel iso/boot/kernel
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o grub.iso iso

clean: 
	rm build/*
	rm grub.iso

install:
	cp build/kernel /boot/kernel-hamtaro
