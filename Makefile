CCFLAGS=-g -I. -Iinclude -fno-builtin -nostdinc
ASMFLAGS=-felf -g
LDFLAGS=-melf_i386
LINKER=linker.ld

all: kernel
	echo done

kernel: asm c
	ld $(LDFLAGS) -o build/kernel build/boot.o build/screen.o build/gdt.o build/idt.o build/memory.o build/pit.o build/main.o build/common.o build/paging.o build/heap.o -T$(LINKER)
	cp build/kernel iso/boot/kernel
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o grub.iso iso
	
asm: src/asm/boot.asm src/asm/screen.asm src/asm/gdt.asm src/asm/idt.asm src/asm/memory.asm src/asm/pit.asm
	nasm $(ASMFLAGS) -o build/boot.o src/asm/boot.asm
	nasm $(ASMFLAGS) -o build/screen.o src/asm/screen.asm
	nasm $(ASMFLAGS) -o build/gdt.o src/asm/gdt.asm
	nasm $(ASMFLAGS) -o build/idt.o src/asm/idt.asm
	nasm $(ASMFLAGS) -o build/memory.o src/asm/memory.asm
	nasm $(ASMFLAGS) -o build/pit.o src/asm/pit.asm

c: src/c/main.c src/c/common.c src/c/paging.c src/c/heap.c
	gcc $(CCFLAGS) -o build/main.o -c src/c/main.c
	gcc $(CCFLAGS) -o build/common.o -c src/c/common.c
	gcc $(CCFLAGS) -o build/paging.o -c src/c/paging.c
	gcc $(CCFLAGS) -o build/heap.o -c src/c/heap.c

clean: 
	rm build/*
	rm grub.iso

install:
	cp build/kernel /boot/kernel-hamtaro
