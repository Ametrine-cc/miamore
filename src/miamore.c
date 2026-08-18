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
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
// #include <string.h>

// | 24-bit Foreground | \033[38;2;<r>;<g>;<b>m  | Truecolor RGB support |
// | ----------------- | ----------------------- | ----------------------|
// | 24-bit Background | \033[48;2;<r>;<g>;<b>m  | Truecolor RGB support |

// globals
typedef void (*cursor_action)(int, int);
typedef void (*cursor_visibility)(const char *cursor);

char temp[512];
static FrameBuffer *b;

typedef struct ASCIIEscapeCodes {
  const char *clear;
  const char *reset_styles;
  const char *show_cursor;
  const char *hide_cursor;
} ASCIIEscapeCodes;

ASCIIEscapeCodes aes_instance = {.clear = "\033[2J",
                                 .reset_styles = "\033[0m",
                                 .show_cursor = "\033[?25h",
                                 .hide_cursor = "\033[?25l"};

ASCIIEscapeCodes *aec = &aes_instance;

int window_width;
int window_height;

// window_size
void calc_window_size(void) {
  struct winsize w;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
    window_height = w.ws_row;
    window_width = w.ws_col;

    // printf("Width in pixels:  %d\n", w.ws_xpixel);
    // printf("Height in pixels: %d\n", w.ws_ypixel);
  } else {
    perror("ioctl TIOCGWINSZ failed");
  }
}

// init function
void init_miamore(void) {
  calc_window_size();

  if (!b) {
    b = malloc(sizeof(FrameBuffer));
    b->data = malloc(1024);
    b->capacity = 1024;
    b->len = 0;
  }
}

// functions
void move_cursor(int x, int y) {
  char seq[32];
  int len = snprintf(seq, sizeof(seq), "\033[%d;%dH", y + 1, x + 1);
  buf_append(b, seq, len);
}

void show_hide(const char *set) {
  snprintf(temp, sizeof(temp), "%s", set);

  buf_append(b, temp, sizeof(temp));
  render_frame(b);
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

// miamore functions
void(manage_cursor)(cursor cursor, position position) {
  switch (cursor) {
  case hide:
    manage_cursor_visibility[cursor](aec->hide_cursor);
    break;
  case visible:
    manage_cursor_visibility[cursor](aec->show_cursor);
    break;
  case move:
    manage_cursor_action[cursor](position.x, position.y);
    break;
  }

  fflush(stdout);
}

void wait_for(seconds wait_time) {
  unsigned int retTime = time(0) + wait_time;
  while (time(0) < retTime)
    ;
}

void restore_window(void) {
  snprintf(temp, sizeof(temp), "\033[1;1H%s", aec->reset_styles);

  buf_append(b, temp, strlen(temp));
  render_frame(b);
  fflush(stdout);
}

void clear_window(void) {
  snprintf(temp, sizeof(temp), "\033[1;1H%s", aec->clear);
  buf_append(b, temp, strlen(temp));
  render_frame(b);
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
  case border:
    current_shape = MANAGE_SHAPE_STR[border];
    // snprintf(temp, sizeof(temp),
    // "side_vert: %s\nside_height: %s\ncorners: %s\n", side_vert,
    // side_height, corners);
    // buf_append(b, temp, sizeof(temp));
    // render_frame(b);

    snprintf(temp, sizeof(temp), "%s", corners);

    move_cursor(window_width, 1);
    buf_append(b, temp, sizeof(temp));
    render_frame(b);

    break;
  default:
    current_shape = "hi";
  }
}
