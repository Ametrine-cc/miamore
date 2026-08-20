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

void user_inputs() {
  char temp[512];

  int said = input();
  snprintf(temp, sizeof(temp), "%c", said);
  manage_cursor(move, ((position){2, 2}));

  draw_text(temp);
}

int main() {
  init_miamore();
  clear_window();

  set_window_bg(COLOR_BLACK);

  manage_cursor(hide);

  // set_fg(COLOR_CYAN);
  draw_border(round_line);

  // draw_shape() draws a shape with "." by default,
  // no presets use draw_shape_ex() for
  // different presets and color built
  // in draw_shape_ex() requires all arguments in the
  // function to be filled as it is made for specialised
  // use, if you dont want this functionality please use
  // draw_shape() instead with the seperate functions.

  manage_cursor(move, ((position){5, 5}));
  draw_shape(rect, ((dimensions){5, 5}));

  // draw_shape_ex is the extended version of draw_shape, you must specify the
  // location of where the shape must be drawn
  draw_shape_ex(rect, ((dimensions){4, 4}), ((position){20, 20}), COLOR_RED,
                rounded_rect);

  // draw_shape_at is an extended version of draw_shape but allows position to
  // be embedded in the function call, meaning that manage_cursor(move) is not
  // needed but position is a required argument.
  draw_shape_at(rect, ((dimensions){4, 4}), ((position){10, 10}));

  manage_cursor(move, ((position){2, 3}));
  set_fg(COLOR_YELLOW);
  draw_text("Hi");

  wait_for(4); // waits for 4 seconds
  clear_window();

  return 0;
}
