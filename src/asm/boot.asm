section .text

global _start
extern movcur
extern initscr
extern init_gdt
extern init_idt
extern init_pit
extern remap_pic
extern kmain

extern gdtr

_start:
	jmp multiboot_entry

	align 32
multiboot_header:
	dd 0x1BADB002
	dd 0x00000003
	dd 0xE4524FFB

multiboot_entry:
	cli
	mov ebp,multiboot_entry
	mov esp,_sys_stack
	call initscr
	mov eax,8
	mov ebx,0
	call movcur
	call init_gdt
	call init_idt
	call init_pit
	call remap_pic
	
	sti
	call kmain

stop:	hlt
	jmp stop

section .bss
	align 32
	resb 65536
_sys_stack:

section .data
