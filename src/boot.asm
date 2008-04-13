section .text

global _start
extern kputchar
extern kputstr
extern clrscr
extern movcur
extern kprntnum
extern kprintf

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
	push string_hello
	push dword 0x7d
	push dword 56
	push dword 0
	mov eax,string_fmt
	call kprintf
	add esp,8

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
string_hello: db 'Hello world!',0
string_fmt: db 'Hello%% %d %d 0x%x',10,'%s',0
