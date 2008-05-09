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

%define MULTIBOOT_MAGIC 0x1BADB002
%define MULTIBOOT_FLAGS 0x00000003

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
	dd MULTIBOOT_MAGIC
	dd MULTIBOOT_FLAGS
	dd -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS) ; checksum

multiboot_entry:
	cli
	mov ebp,multiboot_entry
	mov esp,_sys_stack ; set up a 64k stack
	call initscr ; initialize the screen writing functions (printf, etc)
	mov eax,8
	mov ebx,0
	call movcur ; move cursor to desired mosition
	call init_gdt
	call init_idt
	call init_pit
	call remap_pic
	
	sti
	call kmain ; jump to c kmain() function

halt:	hlt
	jmp halt

section .bss
	align 32
	resb 65536
_sys_stack:

section .data
