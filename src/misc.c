
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
  char *character_buffer;
  int character;

  switch (mode) {
  case Short:
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    character = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    snprintf(character_buffer, MAX_BUFFER_SIZE, "%c", character);

  case Long:
    break;
  }

  return character_buffer;
}
