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
#include <sys/ioctl.h>
#include <unistd.h>

// globals
FrameBuffer *fb = NULL;
int window_width;
int window_height;
int unsigned current_position[2];

typedef void (*cursor_action)(int, int);
typedef void (*cursor_visibility)(const char *cursor);

void check_fb(void) {
  if (!fb) {
    fb = malloc(sizeof(FrameBuffer));
    if (!fb)
      return;

    fb->data = malloc(2048);
    if (!fb->data) {
      free(fb);
      fb = NULL;
      return;
    }

    fb->capacity = 2048;
  }

  fb->len = 0;
}

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
  check_fb();

  // printf("%dx%d", window_width, window_height);
  // manage_cursor(hide);
}

// functions
void move_cursor(int x, int y) {
  char seq[32];
  int len = snprintf(seq, sizeof(seq), "\x1b[%d;%dH", y + 1, x + 1);
  buf_append(fb, seq, len);

  current_position[0] = x + 1;
  current_position[1] = y + 1;
}

void show_hide(const char *set) {
  snprintf(temp_buf, sizeof(temp_buf), "%s", set);

  buf_append(fb, temp_buf, sizeof(temp_buf));
  render_frame(fb);
  fflush(stdout);
}

static cursor_visibility manage_cursor_visibility[] = {
    [hide] = show_hide,
    [visible] = show_hide,
};
static cursor_action manage_cursor_action[] = {
    [move] = move_cursor,
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
