section .text

global _start
extern kputchar
extern clrscr

_start:
	jmp multiboot_entry

	align 4
multiboot_header:
	dd 0x1BADB002
	dd 0x00000003
	dd 0xE4524FFB

multiboot_entry:
	cli
	mov ebp,multiboot_entry
	mov esp,_sys_stack

stop:	hlt
	jmp stop

section .bss
	resb 65536
_sys_stack:
