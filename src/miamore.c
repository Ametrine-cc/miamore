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
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
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

// v0.2.1

void clear(void) { request_screen(clear_t); }
void clear_origin(void) { request_screen(clear_origin_t); }

void wait_for(seconds_t seconds) {
  if (seconds <= 0.0)
    return;

  struct timespec req;
  req.tv_sec = (time_t)seconds;
  req.tv_nsec = (double)((seconds - req.tv_sec) * 1e9);
  nanosleep(&req, NULL);
}

void calc_window_size(void) {
  struct winsize w;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
    window_height = w.ws_row;
    window_width = w.ws_col;
  } else {
    perror("ioctl TIOCGWINSZ failed");
  }
}

int input(void) {
  struct termios oldt, newt;
  int ch;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}

char *input_ex(void) {
  size_t capacity = 16;
  size_t length = 0;

  char *input_buf = malloc(capacity);
  if (!input_buf)
    return NULL;

  input_buf[0] = '\0';

  struct termios oldt, newt;
  int ch;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  while ((ch = getchar()) != EOF && ch != '\n') {

    if (ch == 127 || ch == '\b') {
      if (length > 0) {
        length--;
        input_buf[length] = '\0';

        buf_append(fb, "\b \b", 3);
        render_frame(fb);
      }
    } else {
      if (length + 1 >= capacity) {
        capacity *= 2;
        char *temp = realloc(input_buf, capacity);
        if (!temp) {
          free(input_buf);
          tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
          return NULL;
        }
        input_buf = temp;
      }

      input_buf[length++] = (char)ch;
      input_buf[length] = '\0';

      char char_str[2] = {(char)ch, '\0'};
      buf_append(fb, char_str, 1);
      render_frame(fb);
    }
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return input_buf;
}

bool supports_truecolor(void) {
  const char *colorterm = getenv("COLORTERM");
  if (colorterm != NULL) {
    if (strcmp(colorterm, "truecolor") == 0 ||
        strcmp(colorterm, "24bit") == 0) {
      return true;
    }
  }

  const char *term = getenv("TERM");
  if (term != NULL) {
    if (strstr(term, "direct") != NULL || strstr(term, "truecolor") != NULL ||
        strstr(term, "24bit") != NULL || strcmp(term, "kitty") == 0 ||
        strcmp(term, "alacritty") == 0 || strcmp(term, "wezterm") == 0) {
      return true;
    }
  }

  return false;
}
