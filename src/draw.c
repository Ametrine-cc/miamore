// miamore: The C tui library
// Copyright (C) 2026  Ametrine Foundation

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.   If not, see <https://www.gnu.org/licenses/>

#include "miamore.h"
#include <stddef.h>
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>

static const char *MANAGE_SHAPE_STR[] = {
    [square] = "square",
    [circle] = "circle",
    [rect] = "rect",
    [triangle] = "triangle",
};

void(draw_shape)(shape shape, dimensions dimensions, char *line) {
  const char *current_shape;
  (void)(dimensions);

  switch (shape) {
  case square:
    current_shape = MANAGE_SHAPE_STR[square];
    break;
  case circle:
    current_shape = MANAGE_SHAPE_STR[circle];
    break;
  case rect:
    current_shape = MANAGE_SHAPE_STR[rect];
    break;
  case triangle:
    current_shape = MANAGE_SHAPE_STR[triangle];
    break;
  }
}

static const char *MANAGE_BORDER_STR[][6] = {
    [single_line] = {"┌", "┐", "└", "┘", "─", "│"},
    [double_line] = {"╔", "╗", "╚", "╝", "═", "║"},
    [thick_line] = {"┏", "┓", "┗", "┛", "━", "┃"},
    [round_line] = {"╭", "╮", "╰", "╯", "─", "│"},
    [blocky_line] = {"█", "█", "█", "█", "█", "█"},
};

void draw_border(border_type border_type) {
  int height = window_height;
  int width = window_width;

  if (!fb || height < 2 || width < 2)
    return;

  const char **b = MANAGE_BORDER_STR[border_type];
  char pos_buf[32];

#define APPEND_STR(str) buf_append(fb, str, strlen(str))

#define MOVE_TO(x, y)                                                          \
  do {                                                                         \
    int len = snprintf(pos_buf, sizeof(pos_buf), "\033[%d;%dH", (y), (x));     \
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
}

void draw_text(const char *string) {
  if (!fb || !string)
    return;

  fflush(stdout);
  buf_append(fb, string, strlen(string));
  render_frame(fb);
}
