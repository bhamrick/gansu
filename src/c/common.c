/*
 *   This is part of Hamtaro, a simple operating system.
 *   Copyright (C) 2008  Brian Hamrick
 *
 *   Hamtaro is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include<common.h>

u32int kmalloc_int(u32int sz, int align, u32int* phys) {
	if(align==1 && (placement_address & 0xFFF)) {
		placement_address = (placement_address & 0xFFFFF000) + 0x1000;
	}
	if(phys) {
		*phys = placement_address;
	}
	u32int tmp = placement_address;
	placement_address+=sz;
	return tmp;
}

u32int kmalloc(u32int sz) {
	return kmalloc_int(sz,0,0);
}

u32int kmalloc_a(u32int sz) {
	return kmalloc_int(sz,1,0);
}

u32int kmalloc_p(u32int sz, u32int *phys) {
	return kmalloc_int(sz,0,phys);
}

u32int kmalloc_ap(u32int sz, u32int *phys) {
	return kmalloc_int(sz,1,phys);
}

void bzero(void* tptr, u32int sz) {
	char* ptr = tptr;
	u32int i;
	for(i=0; i<sz; i++) *ptr++=0;
}
