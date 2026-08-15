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
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
// #include <string.h>

// | 24-bit Foreground | \033[38;2;<r>;<g>;<b>m  | Truecolor RGB support |
// | ----------------- | ----------------------- | ----------------------|
// | 24-bit Background | \033[48;2;<r>;<g>;<b>m  | Truecolor RGB support |

// manage strings (for typedef)
static const char *MANAGE_CURSOR_STR[] = {
    [hidden] = "\033[?25l",
    [visible] = "\033[?25h",

};
static const char *MANAGE_SHAPE_STR[] = {
    [square] = "square",
    [circle] = "circle",
    [rect] = "rect",
    [triangle] = "triangle",
};

// miamore misc functions
void manage_cursor(cursor shown) {
  if (shown == hidden) {
    const char *hide = MANAGE_CURSOR_STR[shown];
    printf("%s", hide);
  } else if (shown == visible) {
    const char *hide = MANAGE_CURSOR_STR[shown];
    printf("%s", hide);
  }

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

void draw(shape shape, dimensions width_x_height) {}
