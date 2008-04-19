%define VIDEO 0xB8000
%define ROWS 25
%define COLS 80
%define BYTES 4000

section .text

global kputchar
global kputstr
global initscr
global movcur
global clrscr
global kprntstr
global kprntnum
global kprnthex
global inccur
global kprintf
global kscroll

inccur:
	inc dword [_sys_cur_col]
	cmp dword [_sys_cur_col],COLS
	jl .out
	mov dword [_sys_cur_col],0
	inc dword [_sys_cur_row]
	cmp dword [_sys_cur_row],ROWS
	jl .out
	dec dword [_sys_cur_row]
	pusha
	call kscroll
	popa
.out:
	ret

initscr:
	mov dword [_sys_cur_row],0
	mov dword [_sys_cur_col],0
	
	mov dx,0x3d4
	mov al,0x0f
	out dx,ax
	inc dx
	mov ax,0x00
	out dx,ax
	
	dec dx
	mov ax,0x0e
	out dx,ax
	inc dx
	mov ax,0x20
	out dx,ax
	
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
	call inccur
	jmp .endloop
.incrow:
	mov dword [_sys_cur_col],0
	inc dword [_sys_cur_row]
	cmp dword [_sys_cur_row],ROWS
	jl .endloop
	dec dword [_sys_cur_row]
	pusha
	call kscroll
	popa
.endloop:
	inc ecx
	jmp .loop
.out:
	ret

kprnthex:
	; eax has the number
	push ebp
	mov ebp,esp
	dec esp
	mov byte [esp],0

.loop:
	mov edx,eax
	and edx,15
	cmp edx,9
	jg .let
.num:
	or dl,0x30
	jmp .out
.let:
	add dl,0x57
.out:	
	shr eax,4
	dec esp
	mov byte [esp],dl
	cmp eax,0
	jne .loop
	
	mov eax,esp
	call kprntstr

	mov esp,ebp
	pop ebp
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
	xor ecx,ecx
	mov byte cl,[eax]
	mov eax,[_sys_cur_row]
	mov ebx,[_sys_cur_col]
	mov edx,7
	call kputchar
	popa
	call inccur
	inc eax
	jmp .normal
.newline:
	mov dword [_sys_cur_col],0
	inc dword [_sys_cur_row]
	inc eax
	cmp dword [_sys_cur_row],ROWS
	jl .normal
	dec dword [_sys_cur_row]
	pusha
	call kscroll
	popa
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
	pusha
	mov eax,[ebp+ebx]
	call kprnthex
	popa
	add ebx,4
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

kscroll:
	mov edx,VIDEO
	xor ebx,ebx
	mov ecx,2*COLS
.loop:
	mov al,[edx+ecx]
	mov byte [edx+ebx],al
	inc ebx
	inc ecx
	cmp ecx,BYTES
	jl .loop
.loop2:
	mov byte [edx+ebx],0
	inc ebx
	cmp ebx,BYTES
	jl .loop2
	ret

section .bss
_sys_cur_row:
	resd 1
_sys_cur_col:
	resd 1
