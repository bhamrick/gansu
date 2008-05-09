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

global inb ; u32int inb(u32int);
global outb ; void outb(u32int,u32int);

inb:
	mov edx,[esp+4]
	xor eax,eax
	in al,dx
	ret

outb:
	mov edx,[esp+4]
	mov eax,[esp+8]
	out dx,ax
	ret
