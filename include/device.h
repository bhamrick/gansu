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

#ifndef DEVICE_H
#define DEVICE_H

#include<common.h>

// Character devices
// The buffer is stored one-dimensionally.
// The view is rows by cols
// To get to the space directly below the character, add width to the index
// So buffer[width] is directly below buffer[0]
// This allows for optimizing iteration through lines
typedef struct char_dev {
	u8int* buffer;
	int rows, cols, width, ind;
	int (*write)(struct char_dev*,void*,size_t);
	int (*read)(struct char_dev*,void*,size_t);
} char_dev_t;

char_dev_t* char_dev(int,int,int,int(*)(char_dev_t*,void*,size_t),int(*)(char_dev_t*,void*,size_t));
int write(char_dev_t*,void*,size_t);
int read(char_dev_t*,void*,size_t);

#endif
