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
#include <string.h>

static colors_str true_fg_colors_instance = {
    .red_str = "\x1b[38;2;231;76;60m",
    .orange_str = "\x1b[38;2;230;126;34m",
    .yellow_str = "\x1b[38;2;241;196;15m",
    .green_str = "\x1b[38;2;46;204;113m",
    .blue_str = "\x1b[38;2;52;152;219m",
    .pink_str = "\x1b[38;2;232;67;147m",
    .purple_str = "\x1b[38;2;142;68;173m",
    .cyan_str = "\x1b[38;2;0;206;201m",
    .magenta_str = "\x1b[38;2;253;121;168m",
    .black_str = "\x1b[38;2;0;0;0m",
    .white_str = "\x1b[38;2;255;255;255m",
};

static colors_str true_bg_colors_instance = {
    .red_str = "\x1b[48;2;231;76;60m",
    .orange_str = "\x1b[48;2;230;126;34m",
    .yellow_str = "\x1b[48;2;241;196;15m",
    .green_str = "\x1b[48;2;46;204;113m",
    .blue_str = "\x1b[48;2;52;152;219m",
    .pink_str = "\x1b[48;2;232;67;147m",
    .purple_str = "\x1b[48;2;142;68;173m",
    .cyan_str = "\x1b[48;2;0;206;201m",
    .magenta_str = "\x1b[48;2;253;121;168m",
    .black_str = "\x1b[48;2;0;0;0m",
    .white_str = "\x1b[48;2;255;255;255m",
};

static colors_str rgb_fg_colors_instance = {
    .red_str = "\x1b[38;5;196m",
    .orange_str = "\x1b[38;5;208m",
    .yellow_str = "\x1b[38;5;220m",
    .green_str = "\x1b[38;5;40m",
    .blue_str = "\x1b[38;5;39m",
    .pink_str = "\x1b[38;5;204m",
    .purple_str = "\x1b[38;5;97m",
    .cyan_str = "\x1b[38;5;45m",
    .magenta_str = "\x1b[38;5;211m",
    .black_str = "\x1b[38;5;16m",
    .white_str = "\x1b[38;5;231m",
};

static colors_str rgb_bg_colors_instance = {
    .red_str = "\x1b[48;5;196m",
    .orange_str = "\x1b[48;5;208m",
    .yellow_str = "\x1b[48;5;220m",
    .green_str = "\x1b[48;5;40m",
    .blue_str = "\x1b[48;5;39m",
    .pink_str = "\x1b[48;5;204m",
    .purple_str = "\x1b[48;5;97m",
    .cyan_str = "\x1b[48;5;45m",
    .magenta_str = "\x1b[48;5;211m",
    .black_str = "\x1b[48;5;16m",
    .white_str = "\x1b[48;5;231m",
};

static colors_str *true_bg_colors = &true_bg_colors_instance;
static colors_str *true_fg_colors = &true_fg_colors_instance;

static colors_str *rgb_fg_colors = &rgb_fg_colors_instance;
static colors_str *rgb_bg_colors = &rgb_bg_colors_instance;

char *give_color(colors_t color) {
  check_init();

  static int tc_supported = -1;
  if (tc_supported == -1) {
    tc_supported = supports_truecolor() ? 1 : 0;
  }

  switch (color) {
  case red:
    return tc_supported ? true_fg_colors->red_str : rgb_fg_colors->red_str;
  case orange:
    return tc_supported ? true_fg_colors->orange_str
                        : rgb_fg_colors->orange_str;
  case yellow:
    return tc_supported ? true_fg_colors->yellow_str
                        : rgb_fg_colors->yellow_str;
  case green:
    return tc_supported ? true_fg_colors->green_str : rgb_fg_colors->green_str;
  case blue:
    return tc_supported ? true_fg_colors->blue_str : rgb_fg_colors->blue_str;
  case pink:
    return tc_supported ? true_fg_colors->pink_str : rgb_fg_colors->pink_str;
  case purple:
    return tc_supported ? true_fg_colors->purple_str
                        : rgb_fg_colors->purple_str;
  case cyan:
    return tc_supported ? true_fg_colors->cyan_str : rgb_fg_colors->cyan_str;
  case magenta:
    return tc_supported ? true_fg_colors->magenta_str
                        : rgb_fg_colors->magenta_str;
  case black:
    return tc_supported ? true_fg_colors->black_str : rgb_fg_colors->black_str;
  case white:
    return tc_supported ? true_fg_colors->white_str : rgb_fg_colors->white_str;
  default:
    return "";
  }
}

void set_fg(colors_t color) {
  char *col = give_color(color);

  buf_append(fb, col, strlen(col));
  render_frame(fb);
}

void set_bg(colors_t color) {
  char *col = give_color(color);

  buf_append(fb, col, strlen(col));
  render_frame(fb);
}
