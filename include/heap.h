#ifndef HEAP_H
#define HEAP_H

#define MAGIC_FREE 0xAF12EE60
#define MAGIC_USED 0xDEADBEEF
#define HEAP_SUPER 0x1
#define HEAP_RONLY 0x2

#include<common.h>

typedef struct {
	u32int magic;
	u32int size; // head + sizeof(header_t) + head->size == foot
} header_t;

typedef struct {
	header_t* head;
} footer_t;

typedef struct {
	u32int start;
	u32int size;
	u8int flags;
} heap_t;

heap_t *make_heap(u32int,u32int,u8int);
void *alloc(u32int,u8int,heap_t*);
void free(void*);

#endif
