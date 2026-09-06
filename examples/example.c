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

#include "../src/include/miamore.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
// #include <string.h>

/* Frame 1: Neutral */
const char *f1[] = {" /\\_/\\", "( o.o )", " > ^ <", NULL};

/* Frame 2: Blink */
const char *f2[] = {" /\\_/\\", "( -.- )", " > ^ <", NULL};

/* Frame 3: Wink & Tail */
const char *f3[] = {" /\\_/\\", "( ~.o ) ~", " > ^ <", NULL};

/* Kitten Frames (full) */
const char **kitten_frames[] = {f1, f2, f3, NULL};

// Also works with type casting
// const char **kitten_frames[] = {f1, f2, f3, (const char *[]){"", ""}, NULL};

void input_example() {
  // scanf("", str); alternative to using scanf() fron stdio.h

  char buf[512];

  // short input, single char
  int ch = input();
  snprintf(buf, sizeof(buf), "short-mode said -> %c", ch);
  draw_text(buf);

  // long input multi_char -> till enter_key pressed
  manage_cursor(move, ((position_t){5, 6}));

  char *ch_ex = input_ex();
  manage_cursor(move, ((position_t){5, 7}));
  snprintf(buf, sizeof(buf), "long-mode said -> %s", ch_ex);
  draw_text(buf);
}

void ctest() {
  // can change functionality of init with passing the argmuments .should_clear
  // = false or .enable_mouse = true by defualt the values of these arguments
  // are flipped relative to the ones shouwn in this snippet of documentation.
  // init_miamore();
  // you are required to use the init_miamore() function or most of the miamore
  // functions will fail and return errors (return error then quit at that spot)
  //
  //  init_miamore();
  init_miamore(.should_clear = true, .disable_mouse = true);
  manage_keys(disable);

  // the draw_border command can take 2 arguments, text="" and style=enum. text
  // can be set to any const char array for example '.text="hiiii my amazing
  // program"' and that will be outputed at the top of the border.
  //
  // style is an enum that has 4 distict varients for the border: normal(single
  // line), bold(thicker line), rounded(single line with rounded edges) and
  // block(blocky line). which can be called like this '.style=normal' for
  // example
  //
  // draw_border(.text = "wsg");
  set_fg(white);
  draw_border(.text = "C example!", .theme = thick_l);

  manage_cursor(move, ((position_t){5, 5}));
  manage_cursor(show);

  // draw hello world to the screen "\n" is only needed if you want a new line
  draw_text("Hello,");
  draw_text(" World!\n");

  // miamore has 2 clear functions, clear() -> which clears screen and doesnt
  // move the cursor and clear_origin() which does the same but moves the cursor
  // back to (1, 1)
  //
  // clear();
  // clear_origin();

  manage_cursor(move, ((position_t){5, 10}));

  // position becomes the shape origin (cursor position becomes top left corner)
  draw_shape(rect, .theme = single_l, ((dimensions_t){26, 12}));

  // wait_for(MS(250)); // Wait 250 milliseconds
  wait_for(SECONDS(2)); // Wait for 2 seconds
  // wait_for(2); // Wait for 2 seconds
  clear_origin();

  // Drawing animations in miamore

  manage_cursor(move, ((position_t){5, 5}));
  manage_cursor(hide);

  // Passing a preset via designated initializer
  void *animate_kitty = start_animation(.preset = KITTY, .fps = 4);
  // void *animate_kitty =
  // start_animation(.frames = (const char ***)kitten_frames, .fps = 4);

  while (1) {
    int user = input();

    if ('q' == user) {
      end_animation(animate_kitty);
      break;
    }
  }

  // wait_for(4); // Wait for 4 seconds
  clear_origin();
}

int main(void) {
  // Init miamore
  init_miamore(true, true);
  manage_keys(disable);

  // Use debug
  debug(tui, .error = "test",
        .function = "This is an example of a debug error");

  // Wait for 2 seconds
  wait_for(2.0);

  // Clear screen
  clear_origin();

  // Drawing border
  draw_border("!C test!", thick_l);

  // Managing cursor
  manage_cursor(move, ((position_t){5, 5}));
  manage_cursor(show);

  // Setting foreground color
  set_fg(cyan);

  // Drawing text
  draw_text("Hello, ");
  draw_text("World!");

  // Drawing shapes
  draw_shape(rect, double_l, ((dimensions_t){26, 12}), ((position_t){5, 12}));

  set_fg(white);

  manage_cursor(move, ((position_t){20, 4}));

  // Animation
  void *animate_kitty = start_animation(.preset = KITTY, .fps = 4);

  bool runtime = true;

  while (runtime) {
    int user = input();

    if ('q' == user) {
      clear_origin();
      runtime = false;
    }
  }

  end_animation(animate_kitty);

  // Use debug with console
  debug(console, .function = "test_2",
        .error = "This is an example of a debug error through the console raw "
                 "with printf()");
  return 0;
}
