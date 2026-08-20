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
  rect,
  circle,
  triangle,
} shape;

typedef enum {
  single_line,
  thick_line,
  double_line,
  round_line,
  blocky_line,
} border_type;

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

typedef struct colors_t {
  const char *red;
  const char *orange;
  const char *yellow;
  const char *green;
  const char *blue;
  const char *pink;
  const char *purple;
  const char *cyan;
  const char *magenta;
  const char *black;
  const char *white;
  const char *reset;
} colors_t;

typedef enum {
  COLOR_RED,
  COLOR_ORANGE,
  COLOR_YELLOW,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_PINK,
  COLOR_PURPLE,
  COLOR_CYAN,
  COLOR_MAGENTA,
  COLOR_BLACK,
  COLOR_WHITE,
  COLOR_RESET
} colors;

typedef enum presets { rounded_rect, bold_rect } presets;

typedef struct ASCIIEscapeCodes {
  const char *clear;
  const char *reset_styles;
  const char *show_cursor;
  const char *hide_cursor;
} ASCIIEscapeCodes;

static ASCIIEscapeCodes aes_instance = {.clear = "\x1b[2J",
                                        .reset_styles = "\x1b[0m",
                                        .show_cursor = "\x1b[?25h",
                                        .hide_cursor = "\x1b[?25l"};

static ASCIIEscapeCodes *aec = &aes_instance;

typedef unsigned int seconds;

extern unsigned int current_position[2];
extern int window_width;
extern int window_height;

static char temp_buf[512];

extern FrameBuffer *fb;
void check_fb(void);

// MIAMORE : Functions
void init_miamore(void);
void clear_window(void);
void restore_window(void);

// MIAMORE : Drawing
void(draw_shape)(shape shape, dimensions dimensions, const char *line);

void draw_shape_ex(shape shape, dimensions dimensions, position position,
                   colors color, presets preset);

void(draw_shape_at)(shape shape, dimensions dimensions, position position,
                    const char *line);

void draw_text(const char *text);

void draw_border(border_type border_type);

// MIAMORE : Utilities
void(manage_cursor)(cursor cursor, position position);
void wait_for(seconds wait_time);
int input(void);

void set_fg(colors color);
void set_bg(colors color);
void set_window_bg(colors color);

void buf_append(FrameBuffer *fb, const char *str, size_t len);
void render_frame(FrameBuffer *fb);

// MIAMORE : MACROS

// draw_shape macro
#define DRAW_SHAPE_1(s) (draw_shape)(s, (dimensions){6, 6}, ".")
#define DRAW_SHAPE_2(s, d) (draw_shape)(s, d, ".")
#define DRAW_SHAPE_3(s, d, l) (draw_shape)(s, d, l)

#define GET_DRAW_SHAPE_MACRO(_1, _2, _3, NAME, ...) NAME
#define draw_shape(...)                                                        \
  GET_DRAW_SHAPE_MACRO(__VA_ARGS__, DRAW_SHAPE_3, DRAW_SHAPE_2,                \
                       DRAW_SHAPE_1)(__VA_ARGS__)

// draw_shape_at macro
#define DRAW_SHAPE_AT_1(s, d, p) (draw_shape_at)(s, d, p, ".")
#define DRAW_SHAPE_AT_2(s, d, p, l) (draw_shape_at)(s, d, p, l)

#define GET_DRAW_SHAPE_AT_MACRO(_1, _2, _3, _4, NAME, ...) NAME
#define draw_shape_at(...)                                                     \
  GET_DRAW_SHAPE_AT_MACRO(__VA_ARGS__, DRAW_SHAPE_AT_2,                        \
                          DRAW_SHAPE_AT_1)(__VA_ARGS__)

// manage_cursor macro
#define MANAGE_CURSOR_1(c) (manage_cursor)(c, (position){0, 0})
#define MANAGE_CURSOR_2(c, p) (manage_cursor)(c, p)

#define GET_MANAGE_CURSOR_MACRO(_1, _2, NAME, ...) NAME
#define manage_cursor(...)                                                     \
  GET_MANAGE_CURSOR_MACRO(__VA_ARGS__, MANAGE_CURSOR_2,                        \
                          MANAGE_CURSOR_1)(__VA_ARGS__)
#endif // MIAMORE_H
