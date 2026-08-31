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

#ifndef GLOBAL_H
#define GLOBAL_H

#include "include/miamore.h"
#include <stddef.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

// global vars
static char temp_buf[2048];
static char default_typeface[5][5];

// error
static char error_buf[2048];
extern void write_error(char *error);

// screen_options enum
typedef enum screen_options {
  reset_t,
  clear_t,
  clear_origin_t,
  disable_mouse,
} screen_options;

// init
static bool init;
void check_init(void);

// framebuffer
typedef struct {
  char *data;
  size_t capacity;
  size_t len;
} FrameBuffer;

extern FrameBuffer *fb;
void fb_init(void);

void buf_append(FrameBuffer *fb, const char *str, size_t len);
void render_frame(FrameBuffer *fb);

// request functions
void request_screen(screen_options screen);
void(request_cursor)(cursor_t cursor, position_t position);

#define REQUEST_CURSOR_1(c) (request_cursor)(c, (position_t){0, 0})
#define REQUEST_CURSOR_2(c, p) (request_cursor)(c, p)

#define GET_REQUEST_CURSOR_MACRO(_1, _2, NAME, ...) NAME
#define request_cursor(...)                                                    \
  GET_REQUEST_CURSOR_MACRO(__VA_ARGS__, REQUEST_CURSOR_2,                      \
                           REQUEST_CURSOR_1)(__VA_ARGS__)

// color functions
bool supports_truecolor(void);

typedef struct colors_str {
  char *red_str;
  char *orange_str;
  char *yellow_str;
  char *green_str;
  char *blue_str;
  char *pink_str;
  char *purple_str;
  char *cyan_str;
  char *magenta_str;
  char *black_str;
  char *white_str;
  char *reset_str;
} colors_str;

#endif // GLOBAL_H
