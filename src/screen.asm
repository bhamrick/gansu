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
global kprntstr
global kprntnum
global inccur
global kprintf

inccur:
	inc dword [_sys_cur_col]
	cmp dword [_sys_cur_col],COLS
	jl .out
	mov dword [_sys_cur_col],0
	inc dword [_sys_cur_row]
.out:
	ret

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
	xor ch,ch
	shl dx,8
	or cx,dx
	mov edx,VIDEO
	shl ebx,1
	shl eax,5
	add edx,eax
	shl eax,2
	add edx,eax
	add edx,ebx
	mov word [edx],cx
	ret

kprntstr:
	; eax contains a pointer to the string
	mov ecx,eax
.loop:
	cmp byte [ecx],0
	je .out
	cmp byte [ecx],10
	je .incrow
	pusha
	mov eax,[_sys_cur_row]
	mov ebx,[_sys_cur_col]
	mov ecx,[ecx]
	mov edx,7
	call kputchar
	popa
	inc dword [_sys_cur_col]
	cmp dword [_sys_cur_col],COLS
	jl .endloop
.incrow:
	mov dword [_sys_cur_col],0
	inc dword [_sys_cur_row]
.endloop:
	inc ecx
	jmp .loop
.out:
	ret

kprntnum:
	; eax has the number
	push ebp
	mov ebp,esp
	dec esp
	mov byte [esp],0

.loop:
	mov ebx,10
	xor ecx,ecx
	xor edx,edx
	idiv ebx
	or dl,0x30
	dec esp
	mov byte [esp],dl
	cmp eax,0
	jne .loop
	
	mov eax,esp
	call kprntstr

	mov esp,ebp
	pop ebp
	ret

kputstr:
	; eax has the row
	; ebx has the column
	; ecx contains a pointer to the string
.loop:
	cmp byte [ecx],0
	je .out
	cmp byte [ecx],10
	je .incrow
	pusha
	mov ecx,[ecx]
	mov edx,7
	call kputchar
	popa
	inc ebx
	cmp dword ebx,COLS
	jl .endloop
.incrow:
	xor ebx,ebx
	inc eax
.endloop:
	inc ecx
	jmp .loop
.out:
	ret

kprintf:
	; The most complicated thing that will be written tonight (4/12/08)
	; eax has a pointer to a format string
	; The stack has the rest starting at ebp+8 and going up (so the last one was pushed first)
	push ebp
	mov ebp,esp
	
	mov ebx,8
.normal:
	cmp byte [eax],0
	je near .out
	cmp byte [eax],10
	je .newline
	cmp byte [eax],0x25
	je .percent
	pusha
	mov eax,[_sys_cur_row]
	mov ebx,[_sys_cur_col]
	xor ecx,ecx
	mov cl,[eax]
	xor edx,edx
	mov dl,7
	call kputchar
	popa
	call inccur
	inc eax
	jmp .normal
.newline:
	mov dword [_sys_cur_col],0
	inc dword [_sys_cur_row]
	inc eax
	jmp .normal
.percent:
	inc eax
	cmp byte [eax],0x25
	je .printpercent
	cmp byte [eax],0x64
	je .printint
	cmp byte [eax],0x78
	je .printhex
	cmp byte [eax],0x73
	je .printstr

.printpercent:
	pusha
	mov eax,[_sys_cur_row]
	mov ebx,[_sys_cur_col]
	xor ecx,ecx
	mov cl,0x25
	xor edx,edx
	mov dl,7
	call kputchar
	popa
	call inccur
	jmp .endpercent

.printint:
	pusha
	mov eax,[ebp+ebx]
	call kprntnum
	popa
	add ebx,4
	jmp .endpercent

.printhex:
	; to be implemented
	jmp .endpercent

.printstr:
	pusha
	mov eax,[ebp+ebx]
	call kprntstr
	popa
	add ebx,4
	jmp .endpercent

.endpercent:
	inc eax
	jmp .normal

.out:
	mov esp,ebp
	pop ebp
	ret

section .bss
_sys_cur_row:
	resd 1
_sys_cur_col:
	resd 1
