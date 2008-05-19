/*
 *   This is part of Gansu, a simple operating system.
 *   Copyright (C) 2008  Brian Hamrick
 *
 *   Gansu is free software: you can redistribute it and/or modify
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

#include<keyboard.h>
#include<common.h>
#include<device.h>
#include<heap.h>

void kmain() {
	placement_address=(u32int)&end;
	placement_address+=4;

	init_paging();
	init_kbd();

	u32int *foo = (u32int*)malloc(0x30000);
	u32int *a = (u32int*)malloc(sizeof(u32int));
	u32int *b = (u32int*)malloca(sizeof(u32int));
	free(a); free(b);
	u32int *c = (u32int*)malloc(2*sizeof(u32int));
	ckprintf("foo = 0x%x, a = 0x%x, b = 0x%x, c = 0x%x\n",foo,a,b,c);

	int cr3;
	asm volatile("movl %%cr3, %0" : "=r"(cr3));
	ckprintf("cr3=0x%x\n\n",cr3);
	
	char * str = (char*)malloc(2);
	ckprintf("str = 0x%x\n\n",str);
	while(1) {
		str[0]=getch();
		str[1]=0;
		ckprintf("%s",str);
	}
}

