#ifndef PAGING_H
#define PAGING_H

#include<common.h>

typedef struct page {
	u32int present	: 1;
	u32int rw	: 1;
	u32int user	: 1;
	u32int accessed	: 1;
	u32int dirty	: 1;
	u32int unused	: 7;
	u32int frame	: 20;
} page_t;

typedef struct page_table {
 	page_t pages[1024];
} page_table_t;

typedef struct page_directory {
	page_table_t *tables[1024];
	u32int tablesPhysical[1024];
	u32int physicalAddr;
} page_directory_t;

page_directory_t *kernel_directory, *current_directory;

void init_paging();
void switch_page_directory(page_directory_t*);
page_t *get_page(u32int,int,page_directory_t*);
void page_fault(int);

u32int *frames;
u32int nframes;

#define INDEX_FROM_BIT(a) ((a)>>(5))
#define OFFSET_FROM_BIT(a) ((a)&(31))

static void set_frame(u32int);
static void clear_frame(u32int);
static u32int test_frame(u32int);
static u32int first_frame();

void alloc_frame(page_t*,int,int);
void free_frame(page_t*);

#endif
