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

#ifndef __cplusplus
#include <stdbool.h>
#endif

// Window height and Width from ws.row and ws.col
extern int window_height;
extern int window_width;

// Cursor x and y positions
extern unsigned int cursor_x;
extern unsigned int cursor_y;

// Core miamore global variables
extern bool verbose;

// Core miamore global type definitions
typedef struct {
  bool clear_on_reload;
  bool clear_on_startup;
  bool full_canvas_mode;
} MiamoreSettings;

typedef double seconds_t;
typedef enum { Short, Long } input_mode;

// Core miamore functions
void miamore_init(bool manage_resize_reload, bool enable_verbose);

void miamore_settings_opts(MiamoreSettings settings);
#define miamore_settings(...) miamore_settings((MiamoreSettings){__VA_ARGS__})

// Window utilities
int *get_window_size();

// User utilities
char *input(input_mode mode);

#endif // MIAMORE_H
