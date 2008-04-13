section .text

global _start
extern clrscr
extern movcur
extern kprintf
extern kscroll
extern init_gdt

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
	mov eax,10
	mov ebx,0
	call movcur
	call init_gdt

stop:	hlt
	jmp stop
	nop
	nop
	nop
	nop

section .bss
	align 32
	resb 65536
_sys_stack:

section .data
