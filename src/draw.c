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
#include <string.h>

void draw_text(const char *text) {
  check_init();
  fflush(stdout);

  snprintf(temp_buf, sizeof(temp_buf), "%s", text);

  buf_append(fb, temp_buf, sizeof(temp_buf));
  render_frame(fb);
}

static const char *MANAGE_BORDER_STR[][6] = {
    [single_l] = {"┌", "┐", "└", "┘", "─", "│"},
    [double_l] = {"╔", "╗", "╚", "╝", "═", "║"},
    [thick_l] = {"┏", "┓", "┗", "┛", "━", "┃"},
    [round_l] = {"╭", "╮", "╰", "╯", "─", "│"},
    [blocky_l] = {"█", "█", "█", "█", "█", "█"},
};

void draw_border_opts(const BorderOptions opts) {
  int height = window_height;
  int width = window_width;

  check_init();
  if (height < 2 || width < 2)
    return;

  const char **b = MANAGE_BORDER_STR[opts.theme];
  char pos_buf[32];

#define APPEND_STR(str) buf_append(fb, str, strlen(str))

#define MOVE_TO(x, y)                                                          \
  do {                                                                         \
    int len = snprintf(pos_buf, sizeof(pos_buf), "\x1b[%d;%dH", (y), (x));     \
    buf_append(fb, pos_buf, len);                                              \
  } while (0)

  MOVE_TO(1, 1);
  APPEND_STR(b[0]); // Top-left
  for (int x = 0; x < width - 2; x++) {
    APPEND_STR(b[4]); // Top horizontal
  }
  APPEND_STR(b[1]); // Top-right

  for (int y = 2; y < height; y++) {
    MOVE_TO(1, y);
    APPEND_STR(b[5]); // Left wall

    MOVE_TO(width, y);
    APPEND_STR(b[5]); // Right wall
  }

  MOVE_TO(1, height);
  APPEND_STR(b[2]); // Bottom-left
  for (int x = 0; x < width - 2; x++) {
    APPEND_STR(b[4]); // Bottom horizontal
  }

  MOVE_TO(width, height);
  APPEND_STR(b[3]);

#undef MOVE_TO
#undef APPEND_STR

  render_frame(fb);
  manage_cursor(move, ((position_t){2, 0}));

  if (opts.text != NULL) {
    draw_text(opts.text);
  }
}
