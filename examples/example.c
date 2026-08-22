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

#include "../src/include/miamore.h"
#include <stdio.h>

// void test(void) {
//   clear_window();   // clears terminal window (does NOT move cursor position)
//   restore_window(); // moves cursor to position 1,1 (top left corner) and
//                     // restores default text style
//                     // manage_cursor(move, (position){1, 1})
//                     // does the same thing without restoring text style

//   manage_cursor(move, ((position){.x = 4, .y = 1}));
//   draw_text("dollars billllls\n");

//   // draw_shape(circle, ((dimensions){2, 2}));
//   // or with designated initializers
//   // draw_shape(rect, (dimensions){.width = 2, .height = 2});

//   manage_cursor(hide);
//   wait_for(4); // waits for 4 seconds

//   clear_window(); // clears window and moves back 1,1
//   draw_text("hiii welcome!!!\n");
// }

// void user_inputs() {
//   char temp[512];

//   int said = input();
//   snprintf(temp, sizeof(temp), "%c", said);
//   manage_cursor(move, ((position){2, 2}));

//   draw_text(temp);
// }

int main() {
  init_miamore();
  // clear_window();

  // set_window_bg(COLOR_BLACK);

  // manage_cursor(hide);

  // set_fg(COLOR_CYAN);
  // draw_border(round_line);
  // draw_border(round_line, " example ");

  manage_cursor(move, ((position){5, 5}));
  printf("hi");

  // draw_shape() draws a shape with "." by default, allos you to specify a
  // "line" you want it to be drawn with, recomended 1 char, not promised more
  // than 1 will work well.
  // draw_shape(rect, ((dimensions){5, 5}));

  // manage_cursor(move, ((position){2, 3}));
  // set_fg(COLOR_YELLOW);
  // draw_text("Hi");

  // draw_shape_at(rect, ((dimensions){5, 5}), ((position){10, 10}), "⚪",
  // COLOR_RED);

  // draw_box(((dimensions){30, 30}), ((position){2, 2}));

  // manage_cursor(move, ((position){4, 4}));

  wait_for(8); // waits for 8 seconds
  // clear_window();

  return 0;
}
