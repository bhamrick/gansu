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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include<common.h>
#include<keys.h>

int key_states[8];
unsigned char buffer[256];
u8int buffer_loc, buffer_next;

void set_key(u8int);
void unset_key(u8int);
int test_key(u8int);
void init_kbd();
void keyboard_handler();
unsigned char getch();
unsigned char toUpper(unsigned char);
unsigned char toLower(unsigned char);

#endif
