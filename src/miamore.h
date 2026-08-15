// miamore: The C tui library
// Copyright (C) 2026  Ametrine Foundation

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.   If not, see <https://www.gnu.org/licenses/>

#ifndef MIAMORE_H
#define MIAMORE_H

// MIAMORE : types
typedef enum {
  hide,
  visible,
  move,
} cursor;

typedef enum {
  square,
  circle,
  rect,
  triangle,
} shape;

typedef struct {
  int width;
  int height;
} dimensions;
typedef struct {
  int x;
  int y;
} position;

typedef unsigned int seconds;

// MIAMORE : Functions
void clear_window(void);
void restore_window(void);

void draw(shape shape, dimensions width_x_height);

// MIAMORE : Utilities
void wait_for(seconds wait_time);
void manage_cursor(cursor cursor, position position);

#define MANAGE_CURSOR_1(cursor) manage_cursor(cursor, (position){0, 0})
#define MANAGE_CURSOR_2(cursor, pos) manage_cursor(cursor, pos)

#define GET_MACRO(_1, _2, NAME, ...) NAME
#define manage_cursor(...)                                                     \
  GET_MACRO(__VA_ARGS__, MANAGE_CURSOR_2, MANAGE_CURSOR_1)(__VA_ARGS__)

#endif // MIAMORE_H
