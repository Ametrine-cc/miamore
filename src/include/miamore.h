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

extern unsigned int cursor_x;
extern unsigned int cursor_y;

extern bool verbose;

void miamore_init(bool manage_resize_reload, bool enable_verbose);

int *get_window_size();
bool check_for_window_resize();

#endif // MIAMORE_H
