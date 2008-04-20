section .text

global init_pit
global pit_handler
extern kprintf

init_pit:
	; Sets the pit to 1000 Hz
	mov al,0x36
	out 0x43,al
	mov al,0xa9
	out 0x40,al
	mov al,0x04
	out 0x40,al
	ret

pit_handler:
	cli
	inc dword [ticks]
	mov eax,[ticks]
	mov ebx,1000
	xor ecx,ecx
	xor edx,edx
	idiv ebx
	cmp edx,0
	jne .noprint
.inc:
	mov eax,[seconds]
	mov ebx,[minutes]
	mov ecx,[hours]
	inc eax
	cmp eax,60
	jl .print
	xor eax,eax
	inc ebx
	cmp ebx,60
	jl .print
	xor ebx,ebx
	inc ecx
	cmp ecx,24
	jl .print
	xor ecx,ecx
.print:
	mov [seconds],eax
	mov [minutes],ebx
	mov [hours],ecx
	mov eax,[seconds]
	push eax
	mov eax,[minutes]
	push eax
	mov eax,[hours]
	push eax
	mov eax,[ticks]
	push eax
	mov eax,handler_fmt_str
	call kprintf
	add esp,16
.noprint:
	mov al,0x20
	out 0x20,al
	sti
	iret

section .data
ticks:	dd 0
hours:	dd 0
minutes:dd 0
seconds:dd 0
handler_fmt_str: db 'Ticks: %d (%d:%d:%d)',10,0
