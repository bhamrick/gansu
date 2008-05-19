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
