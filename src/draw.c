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

  printf("here\n");

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
  default:
    current_shape = "hi";
  }
}

void draw_box(int width, int height) {
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

void draw_border(void) {
  draw_box(window_width, window_height);
  return;
}

void draw_text(char *string) {
  if (!fb || !string)
    return;

  fflush(stdout);
  buf_append(fb, string, strlen(string));
  render_frame(fb);
}
