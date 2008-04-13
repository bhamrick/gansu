%define ENTRIES 3

section .text

global init_gdt
extern kprintf

init_gdt:
	mov byte [the_gdt],0x00
	mov byte [the_gdt+1],0x00
	mov byte [the_gdt+2],0x00
	mov byte [the_gdt+3],0x00
	mov byte [the_gdt+4],0x00
	mov byte [the_gdt+5],0x00
	mov byte [the_gdt+6],0x00
	mov byte [the_gdt+7],0x00
	mov byte [the_gdt+8],0xff
	mov byte [the_gdt+9],0xff
	mov byte [the_gdt+10],0x00
	mov byte [the_gdt+11],0x00
	mov byte [the_gdt+12],0x00
	mov byte [the_gdt+13],0x9a
	mov byte [the_gdt+14],0xcf
	mov byte [the_gdt+15],0x00
	mov byte [the_gdt+16],0xff
	mov byte [the_gdt+17],0xff
	mov byte [the_gdt+18],0x00
	mov byte [the_gdt+19],0x00
	mov byte [the_gdt+20],0x00
	mov byte [the_gdt+21],0x92
	mov byte [the_gdt+22],0xcf
	mov byte [the_gdt+23],0x00
	
	mov eax,the_gdt
	mov [gdtr+2],eax
	mov ax,8*ENTRIES
	mov [gdtr],ax
	
	pusha
	xor eax,eax
	mov ax,[gdtr]
	push eax
	mov eax,[gdtr+2]
	push eax
	mov eax,gdt_fmt_str
	call kprintf
	add esp,8
	popa

	lgdt [gdtr]

	jmp 0x08:.reloadcs
.reloadcs:
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	ret

section .bss
the_gdt:
	resb 8*ENTRIES
gdtr:
	resw 1
	resd 1

section .data
gdt_fmt_str: db 'Base=0x%x',10,'Limit=0x%x',10,0
