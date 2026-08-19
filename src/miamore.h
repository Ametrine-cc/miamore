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

// MIAMORE : colors
typedef struct miamore_colors {
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
} miamore_colors;

typedef struct miamore_fg_colors {
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
} miamore_fg_colors;

typedef struct miamore_bg_colors {
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
} miamore_bg_colors;

static miamore_colors colors_instance = {.red = "\x1b[38;2;231;76;60m",
                                         .orange = "\x1b[38;2;230;126;34m",
                                         .yellow = "\x1b[38;2;241;196;15m",
                                         .green = "\x1b[38;2;46;204;113m",
                                         .blue = "\x1b[38;2;52;152;219m",
                                         .pink = "\x1b[38;2;232;67;147m",
                                         .purple = "\x1b[38;2;142;68;173m",
                                         .cyan = "\x1b[38;2;0;206;201m",
                                         .magenta = "\x1b[38;2;253;121;168m",
                                         .black = "\x1b[38;2;0;0;0m",
                                         .white = "\x1b[38;2;255;255;255m"};

static miamore_bg_colors bg_colors_instance = {
    .red = "\x1b[48;2;231;76;60m",
    .orange = "\x1b[48;2;230;126;34m",
    .yellow = "\x1b[48;2;241;196;15m",
    .green = "\x1b[48;2;46;204;113m",
    .blue = "\x1b[48;2;52;152;219m",
    .pink = "\x1b[48;2;232;67;147m",
    .purple = "\x1b[48;2;142;68;173m",
    .cyan = "\x1b[48;2;0;206;201m",
    .magenta = "\x1b[48;2;253;121;168m",
    .black = "\x1b[48;2;0;0;0m",
    .white = "\x1b[48;2;255;255;255m"};

static miamore_fg_colors fg_colors_instance = {
    .red = "\x1b[38;2;231;76;60m",
    .orange = "\x1b[38;2;230;126;34m",
    .yellow = "\x1b[38;2;241;196;15m",
    .green = "\x1b[38;2;46;204;113m",
    .blue = "\x1b[38;2;52;152;219m",
    .pink = "\x1b[38;2;232;67;147m",
    .purple = "\x1b[38;2;142;68;173m",
    .cyan = "\x1b[38;2;0;206;201m",
    .magenta = "\x1b[38;2;253;121;168m",
    .black = "\x1b[38;2;0;0;0m",
    .white = "\x1b[38;2;255;255;255m",
    .reset = "\x1b[0m"};

static miamore_colors *colors = &colors_instance;
static miamore_bg_colors *bg_colors = &bg_colors_instance;
static miamore_fg_colors *fg_colors = &fg_colors_instance;

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

void(manage_cursor)(cursor cursor, position position);
void(draw_shape)(shape shape, dimensions dimensions, const char *line);

// MIAMORE : Drawing
void draw_text(const char *text);
void draw_border(border_type border_type);
// void draw_box(int width, int height);

// MIAMORE : Utilities
void wait_for(seconds wait_time);
int input(void);

void buf_append(FrameBuffer *fb, const char *str, size_t len);
void render_frame(FrameBuffer *fb);

// MIAMORE : MACROS

// draw_shape macro
#define DRAW_SHAPE_1(s) (draw_shape)(s, (dimensions){6, 6}, ".")
#define DRAW_SHAPE_2(s, d) (draw_shape)(s, d, ".")
#define DRAW_SHAPE_3(s, d, l) (draw_shape)(s, d, l)

#define GET_DRAW_MACRO(_1, _2, _3, NAME, ...) NAME
#define draw_shape(...)                                                        \
  GET_DRAW_MACRO(__VA_ARGS__, DRAW_SHAPE_3, DRAW_SHAPE_2,                      \
                 DRAW_SHAPE_1)(__VA_ARGS__)

// manage_cursor macro
#define MANAGE_CURSOR_1(c) (manage_cursor)(c, (position){0, 0})
#define MANAGE_CURSOR_2(c, p) (manage_cursor)(c, p)

#define GET_MANAGE_CURSOR_MACRO(_1, _2, NAME, ...) NAME
#define manage_cursor(...)                                                     \
  GET_MANAGE_CURSOR_MACRO(__VA_ARGS__, MANAGE_CURSOR_2,                        \
                          MANAGE_CURSOR_1)(__VA_ARGS__)
#endif // MIAMORE_H
