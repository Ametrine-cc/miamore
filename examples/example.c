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
// #include <stdio.h>
#include <stdbool.h>

int main(void) {
  // can change functionality of init with passing the argmuments .should_clear
  // = false or .enable_mouse = true by defualt the values of these arguments
  // are flipped relative to the ones shouwn in this snippet of documentation.
  // init_miamore();
  init_miamore(.should_clear = true);
  manage_cursor(hide);

  manage_cursor(move, ((position_t){5, 5}));
  manage_cursor(show);
  // draw_text("hi");
  // clear();

  // wait_for(MS(250)); // Wait 250 milliseconds (e.g. for spinner animation)
  // wait_for(SECONDS(2));
  wait_for(8); // waits for 8 seconds

  return 0;
}
