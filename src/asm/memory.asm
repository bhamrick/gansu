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
