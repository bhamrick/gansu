section .text

global _sys_bzero
global _sys_memcpy

_sys_bzero:
	; eax = addr
	; ebx = size
.loop:
	cmp ebx,0
	jle .out
	mov byte [eax],0
	inc eax
	dec ebx
	jmp .loop
.out:
	ret

_sys_memcpy:
	; eax = dest
	; ebx = src
	; ecx = size
.loop:
	cmp ecx,0
	jle .out
	mov dl,[ebx]
	mov [eax],dl
	inc eax
	inc ebx
	dec ecx
	jmp .loop
.out:
	ret
