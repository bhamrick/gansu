#include<heap.h>

heap_t *make_heap(u32int start, u32int size, u32int maxsize, u8int flags) {
	if((size & 0xFFF) != 0) {
		size &= 0xFFFFF000;
		size += 0x1000;
	}
	if((start & 0xFFF) != 0) {
		start &= 0xFFFFF000;
		start += 0x1000;
	}
	heap_t *heap = (heap_t*)kmalloc(sizeof(heap_t));
	heap->start = start;
	heap->size = size;
	heap->maxsize = maxsize;
	heap->flags = flags;

	header_t* head = (header_t*)start;
	head->magic = MAGIC_FREE;
	head->size = size-sizeof(footer_t);

	footer_t* foot = (footer_t*)(start+size-sizeof(footer_t));
	foot->head = head;

	return heap;
}

void *alloc(u32int size, u8int aligned, heap_t* heap) {
	u32int real_size = size+sizeof(header_t)+sizeof(footer_t);
	header_t* head = (header_t*)heap->start;
	while(1) {
		if((u32int)head >= heap->start+heap->size) return 0;
		if(head->magic == MAGIC_FREE) {
			if(head->size >= real_size) {
				break;
			}
		}
		head = head + head->size + sizeof(header_t) + sizeof(footer_t);
	}
	footer_t* foot = (footer_t*)(head + sizeof(header_t) + head->size);
	header_t* next = head + head->size + sizeof(header_t) + sizeof(footer_t);
	foot->head = next;
	next->size = head->size - real_size;
	next->magic = MAGIC_FREE;
	head->magic = MAGIC_USED;
	head->size = size;
	foot = (footer_t*)(head + sizeof(header_t) + head->size);
	foot->head = head;

	return head+sizeof(header_t);
}

void free(void* ptr) {
	header_t* head = (header_t*)ptr;
}
