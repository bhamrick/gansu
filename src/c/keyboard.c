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

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
  '9', '0', '-', '=', '\b', '\t',
  'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '\'', '`',   0,
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',
  'm', ',', '.', '/',   0,	
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void init_kbd() {
	buffer_loc = 0;
	buffer_next = 0;
	
	u8int i;
	for(i = 0; i<128; i++) shift[i]=i;
	shift['a']='A';
	shift['b']='B';
	shift['c']='C';
	shift['d']='D';
	shift['e']='E';
	shift['f']='F';
	shift['g']='G';
	shift['h']='H';
	shift['i']='I';
	shift['j']='J';
	shift['k']='K';
	shift['l']='L';
	shift['m']='M';
	shift['n']='N';
	shift['o']='O';
	shift['p']='P';
	shift['q']='Q';
	shift['r']='R';
	shift['s']='S';
	shift['t']='T';
	shift['u']='U';
	shift['v']='V';
	shift['w']='W';
	shift['x']='X';
	shift['y']='Y';
	shift['z']='Z';

	shift['1']='!';
	shift['2']='@';
	shift['3']='#';
	shift['4']='$';
	shift['5']='%';
	shift['6']='^';
	shift['7']='&';
	shift['8']='*';
	shift['9']='(';
	shift['0']=')';

	shift['[']='{';
	shift[']']='}';
	shift['-']='_';
	shift['=']='+';
	shift['\\']='|';
	shift[';']=':';
	shift['\'']='"';
	shift[',']='<';
	shift['.']='>';
	shift['/']='?';
	shift['`']='~';
}

void keyboard_handler() {
	u8int scancode, pressed;
	scancode=inb(0x60);
	if(scancode & 0x80) {
		unset_key(scancode & ~0x80);
		pressed=0;
	} else {
		set_key(scancode);
		pressed=1;
	}
	scancode &= ~0x80;
	if(pressed && kbdus[scancode]) {
		unsigned char c = kbdus[scancode];
		if(test_key(SCODE_LEFT_SHIFT) || test_key(SCODE_RIGHT_SHIFT)) {
			c = shift[c];
		}
		buffer[buffer_loc]=c;
		buffer_loc++;
		buffer_loc &= 0xFF;
	}
}

void set_key(u8int scode) {
	key_states[scode>>5] |= 1<<(scode & 31);
}

void unset_key(u8int scode) {
	key_states[scode>>5] &= ~(1<<(scode & 31));
}

int test_key(u8int scode) {
	return !!(key_states[scode>>5] & (1<<(scode & 31)));
}

unsigned char getch() {
	while(buffer_loc == buffer_next) {
		asm volatile("hlt");
	}
	unsigned char ans = buffer[buffer_next];
	buffer_next++;
	buffer_next &= 0xFF;
	return ans;
}

unsigned char toUpper(unsigned char c) {
	if(c >= 'a' && c <= 'z') {
		return c + 'A' - 'a';
	}
	return c;
}

unsigned char toLower(unsigned char c) {
	if(c >= 'A' && c <= 'Z') {
		return c + 'a' - 'A';
	}
	return c;
}
