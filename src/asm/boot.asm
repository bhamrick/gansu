;   This is part of Hamtaro, a simple operating system.
;   Copyright (C) 2008  Brian Hamrick
;
;   Hamtaro is free software: you can redistribute it and/or modify
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

section .text

global _start
extern movcur
extern initscr
extern init_gdt
extern init_idt
extern init_pit
extern remap_pic
extern kmain

global halt

_start:
	jmp multiboot_entry

	align 32
multiboot_header:
	dd 0x1BADB002
	dd 0x00000003
	dd 0xE4524FFB

multiboot_entry:
	cli
	mov ebp,multiboot_entry
	mov esp,_sys_stack
	call initscr
	mov eax,8
	mov ebx,0
	call movcur
	call init_gdt
	call init_idt
	call init_pit
	call remap_pic
	
	sti
	call kmain

halt:	hlt
	jmp halt

section .bss
	align 32
	resb 65536
_sys_stack:

section .data
