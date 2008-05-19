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

#ifndef COMMON_H
#define COMMON_H

typedef	unsigned	int	u32int;
typedef	signed		int	s32int;
typedef	unsigned	short	u16int;
typedef	signed		short	s16int;
typedef	unsigned	char	u8int;
typedef	signed		char	s8int;

typedef	unsigned	int	size_t;

extern u32int end;

void register_isr(int,void*);
u32int placement_address;
void ckprintf(char*,...);
u32int kmalloc_int(size_t,int,u32int*);
u32int kmalloc(size_t);
u32int kmalloc_a(size_t);
u32int kmalloc_p(size_t,u32int*);
u32int kmalloc_ap(size_t,u32int*);
void bzero(void*,size_t);
void halt();
u32int inb(u32int);
void outb(u32int,u32int);

#endif
