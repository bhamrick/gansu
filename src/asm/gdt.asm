;   This is part of Gansu, a simple operating system.
;   Copyright (C) 2008  Brian Hamrick
;
;   Gansu is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.
;
;   This program is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with this program.  If not, see <http://www.gnu.org/licenses/>.

global init_gdt

bits 32
align 32

init_gdt:
	lgdt [gdtr]

	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov gs,ax
	mov fs,ax
	mov ss,ax
	
	jmp 0x08:gdt_return

gdt_return:
	ret

section .data

align 8

gdt_begin:
	dd 0
	dd 0
	
	; ring 0 code (0x08)
	dw 0xffff
	dw 0
	db 0
	db 0x9A
	db 0xCF
	db 0
	
	; ring 0 data
	dw 0xffff
	dw 0
	db 0
	db 0x92
	db 0xCF
	db 0
gdt_end:

gdtr:
	dw gdt_end-gdt_begin-1
	dd gdt_begin
