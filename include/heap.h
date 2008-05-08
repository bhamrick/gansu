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

#ifndef HEAP_H
#define HEAP_H

#define KHEAP_START 0xC0000000
#define KHEAP_INITIAL_SIZE 0x20000
#define MAGIC_FREE 0xAF12EE60
#define MAGIC_USED 0xDEADBEEF
#define ALL_MEM 0xFFFFFFFFu

#include<common.h>
#include<paging.h>

typedef struct {
	u32int start_addr;
	u32int end_addr;
	u32int max_addr;
	u8int super;
	u8int ronly;
} heap_t;

typedef struct {
	u32int magic;
	u32int size;
} header_t;

typedef struct {
	header_t* head;
} footer_t;

heap_t *kheap, *cur_heap;

heap_t* create_heap(u32int,u32int,u32int,u8int,u8int);
void* alloc_int(u32int,heap_t*);
void free_int(void*,heap_t*);
void* malloc(u32int);
void switch_heap(heap_t*);
void free(void*);
int expand(u32int,heap_t*);
void init_heap(heap_t*);
header_t* next_head(header_t*);

#endif
