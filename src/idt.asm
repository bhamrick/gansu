%define ENTRIES 256
%macro isr_no_code 1
isr%1:
;	cli
	push dword 0
	push dword %1
	jmp isr_common_stub
%endmacro
%macro isr_err_code 1
isr%1:
;	cli
	push dword %1
	jmp isr_common_stub
%endmacro
%macro register 1
	mov eax,%1
	mov ebx,isr%1
	call _sys_register_isr
%endmacro

section .text

global init_idt
global _sys_register_isr
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
global isr_common_stub
extern _sys_bzero
extern kprintf

init_idt:
	mov eax,the_idt
	mov ebx,8*ENTRIES
	call _sys_bzero
	mov ax,8*ENTRIES
	mov [idtr],ax
	mov eax,the_idt
	mov [idtr+2],eax
	lidt [idtr]

	register 0
	register 1
	register 2
	register 3
	register 4
	register 5
	register 6
	register 7
	register 8
	register 9
	register 10
	register 11
	register 12
	register 13
	register 14
	register 15
	register 16
	register 17
	register 18
	register 19
	register 20
	register 21
	register 22
	register 23
	register 24
	register 25
	register 26
	register 27
	register 28
	register 29
	register 30
	register 31

	ret

_sys_register_isr:
	; eax = num
	; ebx = addr
	; sel = 0x08
	; type_attr = 0x8E
	shl eax,3
	add eax,the_idt
	mov [eax],bx
	shr ebx,16
	mov [eax+6],bx
	mov byte [eax+2],0x08
	mov byte [eax+4],0
	mov byte [eax+5],0x8E
	ret

isr_no_code 0
isr_no_code 1
isr_no_code 2
isr_no_code 3
isr_no_code 4
isr_no_code 5
isr_no_code 6
isr_no_code 7
isr_err_code 8
isr_no_code 9
isr_err_code 10
isr_err_code 11
isr_err_code 12
isr_err_code 13
isr_err_code 14
isr_no_code 15
isr_no_code 16
isr_no_code 17
isr_no_code 18
isr_no_code 19
isr_no_code 20
isr_no_code 21
isr_no_code 22
isr_no_code 23
isr_no_code 24
isr_no_code 25
isr_no_code 26
isr_no_code 27
isr_no_code 28
isr_no_code 29
isr_no_code 30
isr_no_code 31

isr_common_stub:
	mov eax,isr_str_fmt
	call kprintf
	add esp,8
;	sti
	iret

section .bss
the_idt: resb 8*ENTRIES
idtr: resb 6

section .data
isr_str_fmt: db 'Interrupt: %d, Error code: %d',10,0
