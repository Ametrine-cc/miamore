/*
 * miamore - A terminal user interface library
 * Copyright (C) 2026 Ametrine Foundation
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MIAMORE_H
#define MIAMORE_H

#include <stdint.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

// global miamore vars
extern int window_width;
extern int window_height;
void calc_window_size(void);

// global miamore type enums
typedef enum {
  hide,
  show,
  move,
} cursor_t;

typedef struct {
  int x;
  int y;
} position_t;

typedef enum {
  rect,
  triangle,
} shape_t;

typedef enum { single_l, double_l, thick_l } theme_t;

typedef struct {
  int width;
  int height;
} dimensions_t;

// wait_for()
typedef double seconds_t;

#define SECONDS(s) ((seconds_t)(s))
#define MS(m) ((seconds_t)((m) / 1000.0))

void wait_for(seconds_t seconds);

// clear/clear_origin()
void clear(void);        // clear window and keep cursor ar position
void clear_origin(void); // clear window and go to 1, 1

// miamore_init()
typedef struct {
  bool should_clear;
  bool enable_mouse;
} MiamoreOptions;
void init_miamore_opts(MiamoreOptions opts);
#define init_miamore(...) init_miamore_opts((MiamoreOptions){__VA_ARGS__})

// manage_cursor
void(manage_cursor)(cursor_t cursor, position_t position);

#define MANAGE_CURSOR_1(c) (manage_cursor)(c, (position_t){0, 0})
#define MANAGE_CURSOR_2(c, p) (manage_cursor)(c, p)

#define GET_MANAGE_CURSOR_MACRO(_1, _2, NAME, ...) NAME
#define manage_cursor(...)                                                     \
  GET_MANAGE_CURSOR_MACRO(__VA_ARGS__, MANAGE_CURSOR_2,                        \
                          MANAGE_CURSOR_1)(__VA_ARGS__)

// draw functions
void draw_text(const char *text);

typedef struct {
  char *text;
  theme_t theme;
  bool gap;
} BorderOptions;
void draw_border_opts(BorderOptions opts);
#define draw_border(...) draw_border_opts((BorderOptions){__VA_ARGS__})

#endif // MIAMORE_H
