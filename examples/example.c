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

#include "../src/miamore.h"
#include <stdio.h>

void test(void) {
  clear_window();   // clears terminal window (does NOT move cursor position)
  restore_window(); // moves cursor to position 1,1 (top left corner) and
                    // restores default text style
                    // manage_cursor(move, (position){1, 1})
                    // does the same thing without restoring text style

  manage_cursor(move, ((position){.x = 4, .y = 1}));
  draw_text("dollars billllls\n");

  // draw_shape(circle, ((dimensions){2, 2}));
  // or with designated initializers
  // draw_shape(rect, (dimensions){.width = 2, .height = 2});

  manage_cursor(hide);
  wait_for(4); // waits for 4 seconds

  clear_window(); // clears window and moves back 1,1
  draw_text("hiii welcome!!!\n");
}

int main() {
  init_miamore();
  clear_window();

  manage_cursor(hide);
  // draw_text("Hi");
  draw_border();

  wait_for(4); // waits for 4 seconds
  clear_window();

  return 0;
}
