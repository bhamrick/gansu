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

#include<device.h>
#include<common.h>

char_dev_t* char_dev(int rows, int cols, int width, int (*write)(char_dev_t*,void*,size_t), int (*read)(char_dev_t*,void*,size_t)) {
	if(width < cols) { //sanity check
		return (char_dev_t*)0;
	}
	char_dev_t* dev = (char_dev_t*)malloc(sizeof(char_dev));
	dev->rows  =  rows;
	dev->cols  =  cols;
	dev->width = width;
	dev->write = write;
	dev->read  =  read;
	
	dev->buffer = (u8int*)malloc(rows*width);

	return dev;
}

int write(char_dev_t* dev, void* buf, size_t sz) {
	return dev->write(dev,buf,sz);
}

int read(char_dev_t* dev, void* buf, size_t sz) {
	return dev->read(dev,buf,sz);
}
