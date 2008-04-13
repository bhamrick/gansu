CCFLAGS=-g -I. -fno-builtin -nostdinc
ASMFLAGS=-felf -g
LDFLAGS=-melf_i386
LINKER=linker.ld

all: kernel

kernel:
	nasm $(ASMFLAGS) -o build/boot.o src/boot.asm
	nasm $(ASMFLAGS) -o build/screen.o src/screen.asm
	ld $(LDFLAGS) -o kernel build/boot.o build/screen.o -T$(LINKER)
	cp kernel iso/boot/kernel
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o grub.iso iso

clean: 
	rm build/*
	rm kernel
	rm grub.iso
