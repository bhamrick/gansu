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

#include<paging.h>

static void set_frame(u32int frame_addr) {
	u32int frame = frame_addr/0x1000;
	u32int idx = INDEX_FROM_BIT(frame);
	u32int off = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1<<off);
}

static void clear_frame(u32int frame_addr) {
	u32int frame = frame_addr/0x1000;
	u32int idx = INDEX_FROM_BIT(frame);
	u32int off = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1<<off);
}

static u32int test_frame(u32int frame_addr) {
	u32int frame = frame_addr/0x1000;
	u32int idx = INDEX_FROM_BIT(frame);
	u32int off = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1<<off));
}

static u32int first_frame() {
	u32int i, j;
	for(i = 0; i < INDEX_FROM_BIT(nframes); i++) {
		if(frames[i] != 0xFFFFFFFF) {
			for(j = 0; j<32; j++) {
				u32int toTest = 0x1 << j;
				if(!(frames[i]&toTest)) {
					return (i<<5)+j;
				}
			}
		}
	}
	return (u32int)-1;
}

void alloc_frame(page_t* page, int is_kernel, int is_writeable) {
	if(page->frame)
		return;
	u32int idx = first_frame();
	if(idx == (u32int)-1) {
		for(;;);
	}
	set_frame(idx*0x1000);
	page->present=1;
	page->rw=(is_writeable)?1:0;
	page->user=(is_kernel)?0:1;
	page->frame=idx;
}

void free_frame(page_t* page) {
	u32int frame;
	if(!(frame=page->frame)) return;
	clear_frame(frame);
	page->frame=0;
}

void init_paging() {
	u32int mem_end_page = 0x1000000;

	nframes = mem_end_page/0x1000;
	frames = (u32int*)kmalloc(INDEX_FROM_BIT(nframes)*sizeof(u32int));
	bzero(frames, INDEX_FROM_BIT(nframes)*sizeof(u32int));

	kernel_directory=(page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	bzero(kernel_directory, sizeof(page_directory_t));
	current_directory = kernel_directory;
	
	u32int i = 0;
	
	while(i < placement_address) {
		alloc_frame(get_page(i, 1, kernel_directory),0,0);
		i+=0x1000;
	}

	register_isr(14, (void*)page_fault);

	switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t* dir) {
	current_directory = dir;
	asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
	u32int cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(u32int address, int make, page_directory_t* dir) {
	address /= 0x1000;
	u32int table_idx = address / 1024;
	if(dir->tables[table_idx]) {
		return &dir->tables[table_idx]->pages[address%1024];
	} else if(make) {
		u32int tmp;
		dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t),&tmp);
		bzero(dir->tables[table_idx],0x1000);
		dir->tablesPhysical[table_idx] = tmp | 0x7;
		return &dir->tables[table_idx]->pages[address%1024];
	} else return 0;
}

void page_fault(int err) {
	int present = !(err & 0x1);
	int rw = err & 0x2;
	int us = err & 0x4;
	int reserved = err & 0x8;
	int id = err & 0x10;

	ckprintf("Page fault! ( ");
	if(present) ckprintf("present ");
	if(rw) ckprintf("read-only ");
	if(us) ckprintf("user-mode ");
	if(reserved) ckprintf("reserved ");
	ckprintf(")");
	halt();
}
