%define VIDEO 0xB8000
%define ROWS 24
%define COLS 80

section .text

global kputchar

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
