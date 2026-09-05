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

static char *kitten_frames[] = {
    /* Frame 1: Neutral */
    " /\\_/\\ \033[1B\033[7D( o.o )\033[1B\033[7D > ^ < ",

    /* Frame 2: Blink */
    " /\\_/\\ \033[1B\033[7D( -.- )\033[1B\033[7D > ^ < ",

    /* Frame 3: Wink & Tail */
    " /\\_/\\ \033[1B\033[7D( ~.o ) ~\033[1B\033[9D > ^ < ",

    NULL};

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

int main(void) {
  // can change functionality of init with passing the argmuments .should_clear
  // = false or .enable_mouse = true by defualt the values of these arguments
  // are flipped relative to the ones shouwn in this snippet of documentation.
  // init_miamore();
  // you are required to use the init_miamore() function or most of the miamore
  // functions will fail and return errors (return error then quit at that spot)
  //
  //  init_miamore();
  init_miamore(.should_clear = true, .disable_mouse = true);
  // manage_keys(disable);

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
  // set_fg(red);
  // draw_border(.text = "this is an example!", .theme = thick_l);

  // manage_cursor(move, ((position_t){5, 5}));
  // manage_cursor(show);

  // draw hello world to the screen "\n" is only needed if you want a new line
  // draw_text("Hello,");
  // draw_text(" World!\n");

  // miamore has 2 clear functions, clear() -> which clears screen and doesnt
  // move the cursor and clear_origin() which does the same but moves the cursor
  // back to (1, 1)
  //
  // clear();
  // clear_origin();

  // manage_cursor(move, ((position_t){5, 10}));

  // position becomes the shape origin (cursor position becomes top left corner)
  // draw_shape(rect, .theme = single_l, ((dimensions_t){26, 12}));

  // wait_for(MS(250)); // Wait 250 milliseconds
  // wait_for(SECONDS(2)); // Wait for 2 seconds
  // wait_for(2); // Wait for 2 seconds
  // clear_origin();

  // Drawing animations in miamore

  manage_cursor(move, ((position_t){5, 5}));
  // Passing a preset via designated initializer
  void *animate_kitty = start_animation(.frames = kitten_frames, .fps = 4);

  while (1) {
    int user = input();

    if ('q' == user) {
      end_animation(animate_kitty);
      break;
    }

    pthread_mutex_lock(&stdout_mutex);
    printf("%c", user);
    fflush(stdout);
    pthread_mutex_unlock(&stdout_mutex);
  }

  clear_origin();
  // wait_for(4); // Wait for 4 seconds

  return 0;
}
