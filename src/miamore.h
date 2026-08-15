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
  hidden,
  visible,
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

typedef unsigned int seconds;

// MIAMORE : Functions
void clear_window(void);
void restore_window(void);

void draw(shape shape, dimensions width_x_height);

// MISC : Utilities
void wait_for(seconds wait_time);
void manage_cursor(cursor visible);

#endif // MIAMORE_H
