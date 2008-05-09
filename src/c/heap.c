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

void* alloc_int(u32int size, heap_t* heap) {
	header_t* head = (header_t*)(heap->start_addr);
	while(head->magic==MAGIC_USED || head->size < size) head = next_head(head);
	if(head->magic!=MAGIC_FREE) return (void*)0;
	
	void* ans = (void*)((u32int)head + sizeof(header_t));
	if(head->size == ALL_MEM) {
		// This is the only one which might need to expand the heap - This expansion needs to be implemented sometime
		head->magic = MAGIC_USED;
		head->size = size;
		footer_t* foot = (footer_t*)((u32int)head+sizeof(header_t)+head->size);
		foot->head = head;
		header_t* next = (header_t*)((u32int)foot+sizeof(footer_t));;
		next->magic = MAGIC_FREE;
		next->size = ALL_MEM;
	} else if(head->size - size - sizeof(header_t) - sizeof(footer_t) > 0) {
		footer_t *foot, *next_foot;
		next_foot = (footer_t*)((u32int)head + head->size + sizeof(header_t));
		foot = (footer_t*)((u32int)head + size + sizeof(header_t));
		header_t *next = next_head(head);
		
		next->size = head->size - size - sizeof(header_t) - sizeof(footer_t);

		head->magic = MAGIC_USED;
		head->size = size;
		foot->head = head;
		next->magic = MAGIC_FREE;
		next_foot->head = next;
	} else {
		head->magic = MAGIC_USED;
	}
	return ans;
}

void* malloc(u32int size) {
	return alloc_int(size,cur_heap);
}

void free_int(void* p, heap_t* heap) {
	if(!p) return;
	header_t* head = (header_t*)((u32int)p-sizeof(header_t));
	if(head->magic != MAGIC_USED) return;	
	head->magic=MAGIC_FREE;

	header_t* next = (header_t*)((u32int)head + sizeof(header_t) + sizeof(footer_t) + head->size);
	if(next->magic==MAGIC_FREE) {
		if(next->size == ALL_MEM) {
			head->size = ALL_MEM;
		} else {
			head->size = head->size + next->size + sizeof(header_t) + sizeof(footer_t);
			footer_t* foot = (footer_t*)((u32int)head + sizeof(header_t) + head->size);
			foot->head = head;
		}
	}

	if(heap->start_addr != (u32int)head) {
		header_t* prev = ((footer_t*)((u32int)head-sizeof(footer_t)))->head;
		if(prev->magic == MAGIC_FREE) {
			if(head->size == ALL_MEM) {
				prev->size = ALL_MEM;
			} else {
				prev->size = prev->size + head->size + sizeof(header_t) + sizeof(footer_t);
				footer_t* foot = (footer_t*)((u32int)prev + sizeof(header_t) + prev->size);
				foot->head = prev;
			}
		}
	}
}

void free(void* p) {
	free_int(p,cur_heap);
}

void switch_heap(heap_t* heap) {
	cur_heap = heap;
}

int expand(u32int newsize, heap_t* heap) {
	if(newsize < heap->end_addr - heap->start_addr) return 0;
	if(newsize & 0xFFF) {
		newsize &= 0xFFFFF000;
		newsize += 0x1000;
	}
	if(newsize > heap->max_addr - heap->start_addr) return 0;
	u32int i = heap->end_addr - heap->start_addr;
	while(i < newsize) {
		alloc_frame( get_page(heap->start_addr+i, 1, kernel_directory), 
			(heap->super)?1:0, (heap->ronly)?0:1);
		i += 0x1000;
	}
	heap->end_addr = heap->start_addr+newsize;
	return 1;
}

void init_heap(heap_t* heap) {
	header_t* head = (header_t*)(heap->start_addr);
	head->magic = MAGIC_FREE;
	head->size = ALL_MEM;
}

header_t* next_head(header_t* head) {
	return (header_t*)((u32int)head + head->size + sizeof(header_t) + sizeof(footer_t));
}
