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

typedef void (*border)(border_type);

void get_border_char(border_type border_type) {
  printf("\n%s", MANAGE_BORDER_STR[border_type][1]);
}

static border MANAGE_BORDER_TYPES_STR[] = {
    [single_line] = get_border_char, [double_line] = get_border_char,
    [thick_line] = get_border_char,  [round_line] = get_border_char,
    [blocky_line] = get_border_char,
};

void draw_border(border_type border_type) {
  get_border_char(border_type);

  int height = window_height;
  int width = window_width;

  if (!fb || !height || !width)
    return;

  manage_cursor(move, ((position){1, 1}));
  fflush(stdout);
  for (int x = 0; x < width; x++)
    buf_append(fb, "-", 1);
  render_frame(fb);

  for (int y = 2; y < height; y++) {

    // Left wall
    manage_cursor(move, ((position){1, y}));
    fflush(stdout);
    buf_append(fb, "|", 1);
    render_frame(fb);

    // Right wall
    manage_cursor(move, ((position){width, y}));
    fflush(stdout);
    buf_append(fb, "|", 1);
    render_frame(fb);
  }

  // Bottom border
  manage_cursor(move, ((position){1, height}));
  fflush(stdout);
  for (int x = 0; x < width; x++)
    buf_append(fb, "-", 1);
  render_frame(fb);
}

void draw_text(const char *string) {
  if (!fb || !string)
    return;

  fflush(stdout);
  buf_append(fb, string, strlen(string));
  render_frame(fb);
}
