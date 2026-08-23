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

// wait_for()
typedef double seconds_t;

#define SECONDS(s) ((seconds_t)(s))
#define MS(m) ((seconds_t)((m) / 1000.0))

void wait_for(seconds_t seconds);

// clear_window()
void clear_window(void);        // clear window and keep cursor ar position
void clear_origin_window(void); // clear window and go to 1, 1

// miamore_init()
typedef struct {
  bool should_clear;
  bool enable_mouse;
} MiamoreOptions;

void init_miamore_opts(MiamoreOptions opts);

#define init_miamore(...) init_miamore_opts((MiamoreOptions){__VA_ARGS__})

#endif // MIAMORE_H
