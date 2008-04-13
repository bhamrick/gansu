%define VIDEO 0xB8000
%define ROWS 24
%define COLS 80
%define BYTES 3840

section .text

global kputchar
global kputstr
global initscr
global movcur
global clrscr

initscr:
	mov dword [_sys_cur_row],0
	mov dword [_sys_cur_col],0
	ret

movcur:
	mov [_sys_cur_row],eax
	mov [_sys_cur_col],ebx
	ret

clrscr:
	mov edx,VIDEO
	xor ecx,ecx
.loop:
	mov byte [edx+ecx],0
	inc ecx
	cmp dword ecx,BYTES
	jl .loop
	ret

kputchar:
	; Since I don't want to use the stack yet,
	; eax contains the row
	; ebx contains the column
	; ecx contains the character
	; edx contains the attr
	shl edx,8
	or ecx,edx
	mov edx,VIDEO
	shl ebx,1
	shl eax,5
	add edx,eax
	shl eax,2
	add edx,eax
	add edx,ebx
	mov word [edx],cx
	ret

kputstr:
	

section .bss
_sys_cur_row:
	resd 1
_sys_cur_col:
	resd 1
