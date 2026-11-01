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
#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

unsigned int window_height = 0;
unsigned int window_width = 0;

unsigned int cursor_x = 0;
unsigned int cursor_y = 0;

int main(void) {
  int previous_row = -1;
  int previous_col = -1;

  while (true) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
      perror("ioctl");
      return 1;
    }

    if ((int)ws.ws_row != previous_row || (int)ws.ws_col != previous_col) {
      printf("Rows: %u, columns: %u\n", ws.ws_row, ws.ws_col);
      fflush(stdout);

      previous_row = ws.ws_row;
      previous_col = ws.ws_col;
    }

    struct timespec delay = {.tv_sec = 0, .tv_nsec = 200000000};
    nanosleep(&delay, NULL);
  }
}
