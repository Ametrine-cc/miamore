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
#include "include/miamore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

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

  struct termios oldt, newt;
  int ch;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  while ((ch = getchar()) != EOF && ch != '\n') {
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

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  input_buf[length] = '\0';

  return input_buf;
}
