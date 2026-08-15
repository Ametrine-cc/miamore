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

int main() {
  // wait_for(4); // waits for 4 seconds
  printf("Hello, World!\n");
  clear_window(); // clears terminal window and moves cursor to position 1,1
                  // (top left corner)
  draw(rect, (dimensions){2, 2});
  // or with designated initializers
  // draw(rect, (dimensions){.width = 2, .height = 2});

  return 0;
}
