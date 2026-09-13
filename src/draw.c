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

  request_draw((DrawCmd){.type = CMD_TEXT, .text = strdup(text)});
  render_frame();
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

#define APPEND_STR(str)                                                        \
  request_draw((DrawCmd){.type = CMD_TEXT, .text = (char *)(str)})
#define MOVE_TO(x_val, y_val)                                                  \
  request_draw((DrawCmd){.type = CMD_MOVE, .x = (x_val), .y = (y_val)})

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
  APPEND_STR(b[3]); // Bottom-right

#undef MOVE_TO
#undef APPEND_STR

  if (opts.text != NULL) {
    manage_cursor(move, ((position_t){2, 1})); // Move to top-left of border

    char buf[512];
    snprintf(buf, sizeof(buf), " %s ", opts.text);

    request_draw((DrawCmd){.type = CMD_TEXT, .text = strdup(buf)});
  }

  render_frame();
}

void draw_rect(int width, int height, theme_t theme) {
  char temp[64];

  int box_w = (width > 0) ? width : (window_width - cursor_x);
  int box_h = (height > 0) ? height : (window_height - cursor_y);

  if (box_w <= 0 || box_h <= 0)
    return;

  for (int r = cursor_y; r < cursor_y + box_h && r <= window_height; r++) {

    // int n = snprintf(temp, sizeof(temp), "\x1b[%d;%dH", r, cursor_x);
    // buf_append(&fb, temp, (size_t)n);
    request_draw((DrawCmd){.type = CMD_TEXT, .text = temp});

    if (r == cursor_y || r == cursor_y + box_h - 1) {
      // buf_append(&fb, "+", 1);
      request_draw((DrawCmd){.type = CMD_TEXT, .text = "+"});
      for (int c = 0; c < box_w - 2; c++) {
        // buf_append(&fb, "-", 1);
        request_draw((DrawCmd){.type = CMD_TEXT, .text = "-"});
      }
      // buf_append(&fb, "+", 1);
      request_draw((DrawCmd){.type = CMD_TEXT, .text = "+"});
    } else {
      // buf_append(&fb, "|", 1);
      request_draw((DrawCmd){.type = CMD_TEXT, .text = "|"});

      // snprintf(temp, sizeof(temp), "\x1b[%d;%dH", r, cursor_x + box_w - 1);
      int cur = cursor_x + box_w - 1;
      request_draw((DrawCmd){.type = CMD_MOVE, .x = cur});

      // buf_append(&fb, "|", 1);
      request_draw((DrawCmd){.type = CMD_TEXT, .text = "|"});
    }
  }

  render_frame();
}

void draw_shape_opts(shape_t shape, ShapeOptions opts) {
  check_init();
  fflush(stdout);

  switch (shape) {
  case rect:
    draw_rect(opts.dimensions.width, opts.dimensions.height, opts.theme);
    break;
  default:
    break;
  }
}
