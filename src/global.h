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

#include <stddef.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

// global vars
static char temp_buf[2048];

// error
static char error_buf[512];
extern void write_error(char *error);

// screen_options enum
typedef enum screen_options { reset, clear, clear_origin } screen_options;

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

#endif // GLOBAL_H
