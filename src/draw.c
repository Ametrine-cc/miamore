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

#include "global.h"
#include "include/miamore.h"
#include <stdbool.h>
#include <stdio.h>

void draw_text(const char *text) {
  check_init();
  fflush(stdout);

  snprintf(temp_buf, sizeof(temp_buf), "%s", text);

  buf_append(fb, temp_buf, sizeof(temp_buf));
  render_frame(fb);
}

void draw_border_opts(const BorderOptions opts) {
  check_init();

  // draw_text(opts.text);
  int width = window_width;
  int height = window_height;

  fflush(stdout);
  manage_cursor(move, ((position_t){0, 1}));

  for (int x = 0; x < width; x++)
    buf_append(fb, "-", 1);
  render_frame(fb);

  for (int y = 2; y < height; y++) {
    // Left wall
    manage_cursor(move, ((position_t){1, y}));
    fflush(stdout);
    buf_append(fb, "|", 1);
    render_frame(fb);

    // Right wall
    manage_cursor(move, ((position_t){width, y}));
    fflush(stdout);
    buf_append(fb, "|", 1);
    render_frame(fb);
  }

  // Bottom border
  manage_cursor(move, ((position_t){1, height}));
  fflush(stdout);
  for (int x = 0; x < width; x++)
    buf_append(fb, "-", 1);
  render_frame(fb);
}
