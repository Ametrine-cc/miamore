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

// included libraries
#include <stddef.h>

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

typedef struct {
  char *data;
  size_t capacity;
  size_t len;
} FrameBuffer;

typedef struct ASCIIEscapeCodes {
  const char *clear;
  const char *reset_styles;
  const char *show_cursor;
  const char *hide_cursor;
} ASCIIEscapeCodes;

static ASCIIEscapeCodes aes_instance = {.clear = "\033[2J",
                                        .reset_styles = "\033[0m",
                                        .show_cursor = "\033[?25h",
                                        .hide_cursor = "\033[?25l"};

static ASCIIEscapeCodes *aec = &aes_instance;

typedef unsigned int seconds;

static int window_width;
static int window_height;

static char temp_buf[512];

extern FrameBuffer *fb;
void check_fb(void);

// MIAMORE : Functions

void init_miamore(void);

void clear_window(void);
void restore_window(void);

void(manage_cursor)(cursor cursor, position position);
void(draw)(shape shape, dimensions dimensions, char *line);
void draw_text(char *text);
void draw_border();

// MIAMORE : Utilities
void wait_for(seconds wait_time);

void buf_append(FrameBuffer *fb, const char *str, size_t len);
void render_frame(FrameBuffer *fb);

// MIAMORE : MACROS
#define DRAW_1(s) (draw)(s, (dimensions){6, 6}, ".")
#define DRAW_2(s, d) (draw)(s, d, ".")
#define DRAW_3(s, d, l) (draw)(s, d, l)

#define GET_DRAW_MACRO(_1, _2, _3, NAME, ...) NAME
#define draw(...)                                                              \
  GET_DRAW_MACRO(__VA_ARGS__, DRAW_3, DRAW_2, DRAW_1)(__VA_ARGS__)

#define MANAGE_CURSOR_1(c) (manage_cursor)(c, (position){0, 0})
#define MANAGE_CURSOR_2(c, p) (manage_cursor)(c, p)

#define GET_MANAGE_CURSOR_MACRO(_1, _2, NAME, ...) NAME
#define manage_cursor(...)                                                     \
  GET_MANAGE_CURSOR_MACRO(__VA_ARGS__, MANAGE_CURSOR_2,                        \
                          MANAGE_CURSOR_1)(__VA_ARGS__)
#endif // MIAMORE_H
