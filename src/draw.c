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

void draw_rect(int width, int height, theme_t theme) {
  request_draw((DrawCmd){.type = CMD_BOX, .w = width, .h = height});
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
