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

#include<keyboard.h>

void init_kbd() {
}

void keyboard_handler() {
	u8int scancode;
	scancode=inb(0x60);
	if(scancode & 0x80) {
		ckprintf("Released: ");
	} else {
		ckprintf("Pressed: ");
	}
	scancode &= ~0x80;
	switch(scancode) {
		case KEY_LEFT_SHIFT:
		case KEY_RIGHT_SHIFT:
			ckprintf("Shift\n");
			break;
		case KEY_CAPS_LOCK:
			ckprintf("Caps lock\n");
			break;
		case KEY_CTRL:
			ckprintf("Control\n");
			break;
		case KEY_ALT:
			ckprintf("Alt\n");
			break;
		default:
			ckprintf("Scancode 0x%x (%d)\n",scancode,scancode);
	}
}
