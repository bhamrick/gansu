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

#ifndef KEYS_H
#define KEYS_H

#define SCODE_A 0x1e
#define SCODE_B 0x30
#define SCODE_C 0x2e
#define SCODE_D 0x20
#define SCODE_E 0x12
#define SCODE_F 0x21
#define SCODE_G 0x22
#define SCODE_H 0x23
#define SCODE_I 0x17
#define SCODE_J 0x24
#define SCODE_K 0x25
#define SCODE_L 0x26
#define SCODE_M 0x32
#define SCODE_N 0x31
#define SCODE_O 0x18
#define SCODE_P 0x19
#define SCODE_Q 0x10
#define SCODE_R 0x13
#define SCODE_S 0x1f
#define SCODE_T 0x14
#define SCODE_U 0x16
#define SCODE_V 0x2f
#define SCODE_W 0x11
#define SCODE_X 0x2d
#define SCODE_Y 0x15
#define SCODE_Z 0x2c
#define SCODE_0 0x0b
#define SCODE_1 0x02
#define SCODE_2 0x03
#define SCODE_3 0x04
#define SCODE_4 0x05
#define SCODE_5 0x06
#define SCODE_6 0x07
#define SCODE_7 0x08
#define SCODE_8 0x09
#define SCODE_9 0x0a

#define SCODE_SPACE 0x39

#define SCODE_LEFT_SHIFT 0x2a
#define SCODE_RIGHT_SHIFT 0x36
#define SCODE_CAPS_LOCK 0x3a
#define SCODE_TAB 0x0f
#define SCODE_CTRL 0x1d
#define SCODE_ALT 0x38
#define SCODE_ESC 0x01
#define SCODE_TILDE 0x29
#define SCODE_MINUS 0x0c
#define SCODE_EQUALS 0x0d
#define SCODE_BACKSPACE 0x0e
#define SCODE_LBRACKET 0x1a
#define SCODE_RBRACKET 0x1b
#define SCODE_SLASH 0x35
#define SCODE_BACKSLASH 0x2b
#define SCODE_COLON 0x27
#define SCODE_APOSTROPHE 0x28
#define SCODE_ENTER 0x1c
#define SCODE_F1 0x3b
#define SCODE_F2 0x3c
#define SCODE_F3 0x3d
#define SCODE_F4 0x3e
#define SCODE_F5 0x3f
#define SCODE_F6 0x40
#define SCODE_F7 0x41
#define SCODE_F8 0x42
#define SCODE_F9 0x43
#define SCODE_F10 0x44
#define SCODE_F11 0x57
#define SCODE_F12 0x58
#define SCODE_DELETE 0x53
#define SCODE_END 0x4f
#define SCODE_PDN 0x51
#define SCODE_PUP 0x49
#define SCODE_HOME 0x47
#define SCODE_INSERT 0x52
#define SCODE_NUMLOCK 0x45
#define SCODE_SCROLLLOCK 0x46

unsigned char kbdus[128];
unsigned char shift[128];

#endif
