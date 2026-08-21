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

#include "global.h"
#include <stddef.h>
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>

void draw_rect(dimensions dimensions, const char *line) {
  if (!fb || !dimensions.height || !dimensions.width || !line)
    return;

  size_t line_len = strlen(line);

  int start_x = current_position[0];
  int start_y = current_position[1];

  manage_cursor(move, ((position){start_x, start_y}));
  for (int x = 0; x < dimensions.width; x++) {
    buf_append(fb, line, line_len);
  }

  for (int y = 1; y < dimensions.height - 1; y++) {
    int current_y = start_y + y;

    // Left wall
    manage_cursor(move, ((position){start_x, current_y}));
    buf_append(fb, line, line_len);

    // Right wall
    manage_cursor(move,
                  ((position){start_x + dimensions.width - 1, current_y}));
    buf_append(fb, line, line_len);
  }

  if (dimensions.height > 1) {
    manage_cursor(move, ((position){start_x, start_y + dimensions.height - 1}));
    for (int x = 0; x < dimensions.width; x++) {
      buf_append(fb, line, line_len);
    }
  }

  render_frame(fb);
}

void draw_triangle(dimensions dimensions, const char *line) {
  draw_text("triangle");
  draw_text(line);
}

void(draw_shape)(shape shape, dimensions dimensions, const char *line,
                 colors color) {
  switch (shape) {
  case rect:
    draw_rect(dimensions, line);
    break;
  case triangle:
    draw_triangle(dimensions, line);
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
}

void(draw_shape_at)(shape shape, dimensions dimensions, position pos,
                    const char *line, colors color) {
  manage_cursor(move, ((position){pos.x, pos.y}));
  set_fg(color);
  draw_shape(shape, dimensions, line);
}

void draw_text(const char *string) {
  if (!fb || !string)
    return;

  fflush(stdout);
  buf_append(fb, string, strlen(string));
  render_frame(fb);
}
