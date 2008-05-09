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

#include<keyboard.h>
#include<common.h>
#include<heap.h>

void kmain() {
	placement_address=(u32int)&end;
	placement_address+=4;

	init_paging();
	init_kbd();

	u32int* b = (u32int*)malloc(sizeof(u32int));
	*b = 5;
	ckprintf("b = 0x%x, *b = %d\n",b,*b);
	free(b);
	
	char * str = (char*)malloc(2);
	ckprintf("str = 0x%x\n",str);
	while(1) {
		str[0]=getch();
		str[1]=0;
		ckprintf("%s",str);
	}
}
