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

#include<heap.h>

heap_t* create_heap(u32int start, u32int end, u32int max, u8int super, u8int ronly) {
	heap_t* heap = (heap_t*)kmalloc(sizeof(heap_t));
	if(start & 0xFFF) {
		start &= 0xFFFFF000;
		start += 0x1000;
	}

	heap->start_addr=start;
	heap->end_addr=end;
	heap->max_addr=max;
	heap->super=super;
	heap->ronly=ronly;

	return heap;
}

void* alloc_int(u32int size, u8int align, heap_t* heap) {
	u32int* placement = (u32int*)heap->start_addr;
	if(align) {
		if(*placement & 0xFFF) {
			*placement &= 0xFFFFF000;
			*placement += 0x1000;
		}
	}
	void* ans = (void*)*placement;
	*placement+=size;
	return ans;
}

void* malloc(u32int size) {
	return alloc_int(size,0,cur_heap);
}

void* malloca(u32int size) {
	return alloc_int(size,1,cur_heap);
}

void free_int(void* p, heap_t* heap) {
	if(!p) return;
}

void free(void* p) {
	free_int(p,cur_heap);
}

void switch_heap(heap_t* heap) {
	cur_heap = heap;
}

void expand(u32int newsize, heap_t* heap) {
	if(newsize < heap->end_addr - heap->start_addr) return;
	if(newsize & 0xFFF) {
		newsize &= 0xFFFFF000;
		newsize += 0x1000;
	}
	if(newsize > heap->max_addr - heap->start_addr) return;
	u32int i = heap->end_addr - heap->start_addr;
	while(i < newsize) {
		alloc_frame( get_page(heap->start_addr+i, 1, kernel_directory), 
			(heap->super)?1:0, (heap->ronly)?0:1);
		i += 0x1000;
	}
	heap->end_addr = heap->start_addr+newsize;
}

void init_heap(heap_t* heap) {
	u32int* placement = (u32int*)heap->start_addr;
	*placement = (u32int)placement+sizeof(u32int);
}
