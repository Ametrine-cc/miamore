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

// int main(void) {
//   // Init miamore
//   init_miamore(true, true, true);
//   manage_keys(disable);

//   // Use debug
//   debug(tui, .error = "test",
//         .function = "This is an example of a debug error");

//   // must remember to render frames
//   render_frame();

//   // Wait for 2 seconds
//   wait_for(2.0);

//   // Clear screen
//   clear_origin();

//   // Drawing border
//   draw_border("!C test!", thick_l);

//   // Managing cursor
//   manage_cursor(move, ((position_t){5, 5}));
//   manage_cursor(show);

//   // Setting foreground color
//   set_fg(cyan);

//   // Drawing text
//   draw_text("Hello, ");
//   draw_text("World!");

//   // Drawing shapes
//   draw_shape(rect, double_l, ((dimensions_t){26, 12}), ((position_t){5,
//   12}));

//   render_frame(); // rendering frames doesnt have to be straight after draw

//   set_fg(white);

//   // Animation
//   // You should not use manage_cursor() to set the position of an animation
//   void *animate_kitty =
//       start_animation(.preset = KITTY, .fps = 4,
//                       .position = ((position_t){20, 4}), .color = green);

//   set_fg(yellow);
//   manage_cursor(move, ((position_t){4, 4}));
//   draw_text("hiya");

//   render_frame();

//   bool runtime = true;

//   while (runtime) {
//     int user = input();

//     if ('q' == user) {
//       runtime = false;
//     }
//   }

//   end_animation(animate_kitty);
//   close_miamore();

//   // Use debug with console
//   debug(console, .function = "test_2",
//         .error = "This is an example of a debug error through the console raw
//         "
//                  "with printf()");

//   render_frame(); // can be done after close_miamore() as doesn't require
//                   // miamore to be initialised for rendering

//   return 0;
// }

int main(void) {
  // Init miamore
  init_miamore(true, true, true);
  manage_keys(disable);

  // Use debug
  // debug(tui, .error = "test",
  // .function = "This is an example of a debug error");

  // Clear screen
  clear_origin();

  // Drawing border
  draw_shape(rect, thick_l);

  // Managing cursor
  manage_cursor(move, ((position_t){5, 5}));
  manage_cursor(show);

  // Drawing text
  draw_text("Hello, ");
  draw_text("World!");

  render_frame();

  bool runtime = true;

  while (runtime) {
    int user = input();

    if ('q' == user) {
      runtime = false;
    }
  }

  // close_miamore();

  // Use debug with console
  debug(console, .function = "test_2",
        .error = "This is an example of a debug error through the console raw "
                 "with printf()");

  render_frame(); // can be done after close_miamore() as doesn't require
                  // miamore to be initialised for rendering

  return 0;
}
