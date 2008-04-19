section .text

global init_pit
global pit_handler
extern kprintf

init_pit:
	; Sets the pit to 100 Hz
	mov al,0x36
	out 0x43,al
	mov al,0x9b
	out 0x40,al
	mov al,0x2e
	out 0x40,al
	ret

pit_handler:
	cli
	inc dword [ticks]
	mov eax,[ticks]
	mov ebx,100
	xor ecx,ecx
	xor edx,edx
	idiv ebx
	cmp edx,0
	jne .noprint
.print:
	mov eax,[ticks]
	push eax
	mov eax,handler_fmt_str
	call kprintf
	add esp,4
.noprint:
	mov al,0x20
	out 0x20,al
	sti
	iret

section .data
ticks:	dd 0
handler_fmt_str: db 'Ticks: %d',10,0
