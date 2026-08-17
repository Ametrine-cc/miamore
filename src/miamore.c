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
// #include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <string.h>

// | 24-bit Foreground | \033[38;2;<r>;<g>;<b>m  | Truecolor RGB support |
// | ----------------- | ----------------------- | ----------------------|
// | 24-bit Background | \033[48;2;<r>;<g>;<b>m  | Truecolor RGB support |

typedef void (*cursor_action)(int, int);
typedef void (*cursor_visibility)(const char *cursor);

static FrameBuffer *b;

void init_miamore(void) {
  if (!b) {
    b = malloc(sizeof(FrameBuffer));
    b->data = malloc(1024);
    b->capacity = 1024;
    b->len = 0;
  }
}

void move_cursor(int x, int y) {
  char seq[32];
  int len = snprintf(seq, sizeof(seq), "\033[%d;%dH", y + 1, x + 1);
  buf_append(b, seq, len);
}

void show_hide(const char *cursor) {
  printf("%s", cursor);
  fflush(stdout);
}

static cursor_visibility manage_cursor_visibility[] = {
    [hide] = show_hide,
    [visible] = show_hide,
};
static cursor_action manage_cursor_action[] = {
    [move] = move_cursor,
};

static const char *MANAGE_SHAPE_STR[] = {
    [square] = "square",     [circle] = "circle", [rect] = "rect",
    [triangle] = "triangle", [border] = "border",
};

// miamore misc functions
void(manage_cursor)(cursor cursor, position position) {
  switch (cursor) {
  case hide:
    manage_cursor_visibility[cursor]("\033[?25l");
    break;
  case visible:
    manage_cursor_visibility[cursor]("\033[?25h");
    break;
  case move:
    manage_cursor_action[cursor](position.x, position.y);
    break;
  }

  render_frame(b);
  fflush(stdout);
}

void wait_for(seconds wait_time) {
  unsigned int retTime = time(0) + wait_time;
  while (time(0) < retTime)
    ;
}

// miamore functions
void restore_window(void) {
  printf("\033[1;1H\033[0m\n");
  fflush(stdout);
}

void clear_window(void) {
  printf("\033[2J");
  fflush(stdout);
}

void draw_text(char *string) {
  buf_append(b, string, strlen(string));
  render_frame(b);
  fflush(stdout);
}

void(draw)(shape shape, dimensions dimensions, char *side_vert,
           char *side_height, char *corners) {
  const char *current_shape;

  if (shape == rect) {
    current_shape = MANAGE_SHAPE_STR[rect];
  } else {
    current_shape = "hi";
  }

  move_cursor(dimensions.width, dimensions.height); // TEMP
  printf("side_vert: %s\nside_height: %s\ncorners: %s\n", side_vert,
         side_height, corners);

  printf("%s\n", current_shape);
}
