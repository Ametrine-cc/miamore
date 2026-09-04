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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void draw_error(const char *function, const char *text, unsigned error_code) {
  check_init();
  fflush(stdout);

  snprintf(error_buf, sizeof(error_buf), "[%s] -> %s : error_code %d\n",
           function, text, error_code);

  buf_append(fb, error_buf, strlen(error_buf));
  render_frame(fb);

  exit(error_code);
}

void draw_text(const char *text) {
  check_init();
  fflush(stdout);

  buf_append(fb, text, strlen(text));
  render_frame(fb);
}

static const char *THEME_STR[][6] = {
    //             0    1    2    3    4    5
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

  const char **b = THEME_STR[opts.theme];
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
    char buf[512];
    snprintf(buf, sizeof(buf), " %s ", opts.text);
    draw_text(buf);
  }
}

void draw_rect(int width, int height, int theme) {
  if (!height || !width)
    return;
  fflush(stdout);

  int unsigned origin_x = cursor_x;
  int unsigned origin_y = cursor_y;

  const char **st = THEME_STR[theme];

  // check not 1, 1
  if (height <= 1 || width <= 1) {
    snprintf(temp_buf, sizeof(temp_buf),
             "under or equal to 1x1, not supported");
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    return;
  }

  // Top-Left Corner
  manage_cursor(move, ((position_t){origin_x, origin_y}));
  buf_append(fb, st[0], strlen(st[0]));
  render_frame(fb);

  // Top Bar
  manage_cursor(move, ((position_t){origin_x + 1, origin_y}));
  for (int x = 2; x < width; x++) {
    buf_append(fb, st[4], strlen(st[4]));
  }
  render_frame(fb);

  // Top-Right Corner
  manage_cursor(move, ((position_t){origin_x + width - 1, origin_y}));
  buf_append(fb, st[1], strlen(st[1]));
  render_frame(fb);

  // Right Wall
  for (int y = 1; y < height - 1; y++) {
    manage_cursor(move, ((position_t){origin_x + width - 1, origin_y + y}));
    buf_append(fb, st[5], strlen(st[5]));
    render_frame(fb);
  }

  // Left Wall
  for (int y = 1; y < height - 1; y++) {
    manage_cursor(move, ((position_t){origin_x, origin_y + y}));
    buf_append(fb, st[5], strlen(st[5]));
    render_frame(fb);
  }

  // Bottom-Left Corner
  manage_cursor(move, ((position_t){origin_x, origin_y + height - 1}));
  buf_append(fb, st[2], strlen(st[2]));
  render_frame(fb);

  // Bottom Bar
  manage_cursor(move, ((position_t){origin_x + 1, origin_y + height - 1}));
  for (int x = 2; x < width; x++) {
    buf_append(fb, st[4], strlen(st[4]));
  }
  render_frame(fb);

  // Bottom-Right Corner
  manage_cursor(move,
                ((position_t){origin_x + width - 1, origin_y + height - 1}));
  buf_append(fb, st[3], strlen(st[3]));
  render_frame(fb);

  manage_cursor(move, ((position_t){origin_x, origin_y + height + 1}));

  fflush(stdout);
}

void draw_shape_opts(shape_t shape, ShapeOptions opts) {
  check_init();
  manage_cursor(move, ((position_t){opts.position.x, opts.position.y}));
  fflush(stdout);

  switch (shape) {
  case rect:
    draw_rect(opts.dimensions.width, opts.dimensions.height, opts.theme);
    break;
  default:
    break;
  }
}
