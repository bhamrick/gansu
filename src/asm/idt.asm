%define ENTRIES 256
%macro isr_no_code 1
global isr%1
isr%1:
	cli
	push dword 0
	push dword %1
	jmp isr_common_stub
%endmacro
%macro isr_err_code 1
global isr%1
isr%1:
	cli
	push dword %1
	jmp isr_common_stub
%endmacro
%macro register 1
	mov eax,%1
	mov ebx,isr%1
	call _sys_register_isr
%endmacro
%macro irq 1
global irq%1
irq%1:
	cli
	push dword %1
	jmp irq_common_stub
%endmacro
%macro register_irq 1
	mov eax,%1
	add eax,32
	mov ebx,irq%1
	call _sys_register_isr
%endmacro

section .text

global init_idt
global _sys_register_isr
global isr_common_stub
global irq_common_stub
global remap_pic
extern _sys_bzero
extern kprintf
extern pit_handler

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

	mov eax,32
	mov ebx,pit_handler
	call _sys_register_isr
	register_irq 1
	register_irq 2
	register_irq 3
	register_irq 4
	register_irq 5
	register_irq 6
	register_irq 7
	register_irq 8
	register_irq 9
	register_irq 10
	register_irq 11
	register_irq 12
	register_irq 13
	register_irq 14
	register_irq 15

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

global register_isr
register_isr:
	mov eax,[esp+4]
	mov ebx,[esp+8]
	jmp _sys_register_isr

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
; No irq 0 because I have a separate handler
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15


isr_common_stub:
	mov eax,isr_str_fmt
	call kprintf
	add esp,8
	sti
	iret

irq_common_stub:
	mov eax,irq_str_fmt
	call kprintf
	pop eax
	cmp eax,8
	jl .master
.slave:
	mov al,0x20
	out 0xa0,al
.master:
	mov al,0x20
	out 0x20,al
	sti
	iret

remap_pic:
	mov al,0x11
	out 0x20,al
	mov al,0x11
	out 0xa0,al
	mov al,0x20
	out 0x21,al
	mov al,0x28
	out 0xa1,al
	mov al,0x04
	out 0x21,al
	mov al,0x02
	out 0xa1,al
	mov al,0x01
	out 0x21,al
	mov al,0x01
	out 0xa1,al
	mov al,0x00
	out 0x21,al
	mov al,0x00
	out 0xa1,al
	ret

section .bss
the_idt: resb 8*ENTRIES
idtr: resb 6

section .data
isr_str_fmt: db 'Interrupt: %d, Error code: %d',10,0
irq_str_fmt: db 'IRQ: %d',10,0
