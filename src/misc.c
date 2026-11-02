
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
#include "include/miamore_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void return_debug(const char *function, const char *message) {
  if (message == NULL)
    return;

  if (verbose)
    printf("[%s] %s\n", function, message);
  fflush(stdout);
}

void wait_for(seconds_t seconds) {
  if (seconds <= 0.0)
    return;

  struct timespec req;
  req.tv_sec = (time_t)seconds;
  req.tv_nsec = (double)((seconds - req.tv_sec) * 1e9);
  nanosleep(&req, NULL);
}

char *input(input_mode mode) {
  struct termios oldt, newt;
  int character;

  size_t capacity = 16;
  size_t length = 0;

  char *character_buffer = malloc(2);
  char *input_buf = malloc(capacity);

  switch (mode) {
  case Short:
    if (!character_buffer)
      return NULL;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    character = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    snprintf(character_buffer, 2, "%c", (char)character);
    return character_buffer;

  case Long:
    if (!input_buf)
      return NULL;

    input_buf[0] = '\0';
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
          write(STDOUT_FILENO, "\b \b", 3);
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

        write(STDOUT_FILENO, &ch, 1);
      }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return input_buf;
  }

  return NULL;
}
