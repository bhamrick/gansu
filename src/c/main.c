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
#include<heap.h>

void kmain() {
	placement_address=(u32int)&end;
	placement_address+=4;
	ckprintf("end=0x%x, &end=0x%x\n",end,&end);
	ckprintf("placement_address=0x%x\n",placement_address);

	init_paging();
	init_kbd();
	
	u32int a = (u32int)malloc(0x8);
	u32int b = (u32int)malloc(0x1000);
	u32int c = (u32int)malloc(0x8);
	u32int e = (u32int)malloca(0x1);
	ckprintf("a=0x%x, b=0x%x, c=0x%x, e=0x%x\n",a,b,c,e);
	u32int *d = (u32int*)a;
	*d = 0x600DB0B1;
	ckprintf("d=0x%x, *d=0x%x\n",d,*d);
}
