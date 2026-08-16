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

void(draw)(shape shape, dimensions dimensions, char *side_vert,
           char *side_height, char *corners);

#define DRAW_1(s) (draw)(s, (dimensions){10, 10}, "#", "#", "#")
#define DRAW_2(s, d) (draw)(s, d, "#", "#", "#")
#define DRAW_3(s, d, sv) (draw)(s, d, sv, "#", "#")
#define DRAW_4(s, d, sv, sh) (draw)(s, d, sv, sh, "#")
#define DRAW_5(s, d, sv, sh, c) (draw)(s, d, sv, sh, c)

#define GET_DRAW_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define draw(...)                                                              \
  GET_DRAW_MACRO(__VA_ARGS__, DRAW_5, DRAW_4, DRAW_3, DRAW_2,                  \
                 DRAW_1)(__VA_ARGS__)

// MIAMORE : Utilities
void wait_for(seconds wait_time);

void(manage_cursor)(cursor cursor, position position);

#define MANAGE_CURSOR_1(c) (manage_cursor)(c, (position){0, 0})
#define MANAGE_CURSOR_2(c, p) (manage_cursor)(c, p)

#define GET_MANAGE_CURSOR_MACRO(_1, _2, NAME, ...) NAME
#define manage_cursor(...)                                                     \
  GET_MANAGE_CURSOR_MACRO(__VA_ARGS__, MANAGE_CURSOR_2,                        \
                          MANAGE_CURSOR_1)(__VA_ARGS__)
#endif // MIAMORE_H
