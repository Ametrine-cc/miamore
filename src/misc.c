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
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void wait_for(seconds wait_time) {
  unsigned int retTime = time(0) + wait_time;
  while (time(0) < retTime)
    ;
}

void restore_window(void) {
  snprintf(temp_buf, sizeof(temp_buf), "\x1b[1;1H%s", aec->reset_styles);

  buf_append(fb, temp_buf, strlen(temp_buf));
  render_frame(fb);
  fflush(stdout);
}

void clear_window(void) {
  snprintf(temp_buf, sizeof(temp_buf), "\x1b[1;1H%s", aec->clear);
  buf_append(fb, temp_buf, strlen(temp_buf));
  render_frame(fb);
  fflush(stdout);
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
