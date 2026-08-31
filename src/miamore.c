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

#include "include/miamore.h"
#include "global.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

FrameBuffer *fb = NULL;
int unsigned window_width;
int unsigned window_height;

int unsigned cursor_x;
int unsigned cursor_y;

bool enable_truecolor;

void fb_init(void) {
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

void init_miamore_opts(const MiamoreOptions opts) {
  init = true;
  calc_window_size();
  fb_init();

  if (opts.should_clear) {
    request_screen(clear_origin_t);
  }
  if (opts.disable_mouse) {
    request_screen(disable_mouse);
  }
}

void check_init(void) {
  if (!init) {
    snprintf(error_buf, sizeof(error_buf), "miamore not initialised");
    write_error(error_buf);
  } else {
    return;
    ;
  }
}

void write_error(char *error) {
  printf("[error] %s\n", error);
  exit(1);
}

// miamore functions
void(manage_cursor)(cursor_t cursor, position_t position) {
  switch (cursor) {
  case hide:
    request_cursor(hide);
    break;
  case show:
    request_cursor(show);
    break;
  case move:
    request_cursor(move, ((position_t){position.x, position.y}));
    break;
  }
}

__attribute__((destructor)) static void lib_auto_cleanup(void) {
  tcflush(STDIN_FILENO, TCIFLUSH);

  struct termios t;
  if (tcgetattr(STDIN_FILENO, &t) == 0) {
    t.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
  }
}

void disable_keyboard_echo(void) {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void restore_keyboard_echo(void) {
  tcflush(STDIN_FILENO, TCIFLUSH);

  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void test(char *string) { printf("%s\n", string); }

void manage_keys(keys_t keyboard) {
  check_init();
  fflush(stdout);

  switch (keyboard) {
  case enable:
    restore_keyboard_echo();
    break;
  case disable:
    disable_keyboard_echo();
    break;
  }
}
