CFLAGS=-g -Iinclude -fno-builtin -nostdinc -m32
ASMFLAGS=-felf -g
LDFLAGS=-melf_i386
LINKER=linker.ld

OBJECTS=build/boot.o build/screen.o build/gdt.o build/idt.o build/memory.o build/pit.o build/common.asm.o build/main.o build/common.c.o build/paging.o build/keyboard.o build/heap.o build/device.o

all: kernel
	echo done

kernel: asm c
	ld $(LDFLAGS) -o build/kernel $(OBJECTS) -T$(LINKER)
	cp build/kernel iso/boot/kernel
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o grub.iso iso
	
asm: src/asm/boot.asm src/asm/screen.asm src/asm/gdt.asm src/asm/idt.asm src/asm/memory.asm src/asm/pit.asm src/asm/common.asm
	mkdir -p build
	nasm $(ASMFLAGS) -o build/boot.o src/asm/boot.asm
	nasm $(ASMFLAGS) -o build/screen.o src/asm/screen.asm
	nasm $(ASMFLAGS) -o build/gdt.o src/asm/gdt.asm
	nasm $(ASMFLAGS) -o build/idt.o src/asm/idt.asm
	nasm $(ASMFLAGS) -o build/memory.o src/asm/memory.asm
	nasm $(ASMFLAGS) -o build/pit.o src/asm/pit.asm
	nasm $(ASMFLAGS) -o build/common.asm.o src/asm/common.asm

c: src/c/main.c src/c/common.c src/c/paging.c src/c/keyboard.c src/c/heap.c src/c/device.c
	mkdir -p build
	gcc $(CFLAGS) -o build/main.o -c src/c/main.c
	gcc $(CFLAGS) -o build/common.c.o -c src/c/common.c
	gcc $(CFLAGS) -o build/paging.o -c src/c/paging.c
	gcc $(CFLAGS) -o build/keyboard.o -c src/c/keyboard.c
	gcc $(CFLAGS) -o build/heap.o -c src/c/heap.c
	gcc $(CFLAGS) -o build/device.o -c src/c/device.c

clean: 
	rm build/*
	rm grub.iso

install:
	cp build/kernel /boot/kernel-gansu
