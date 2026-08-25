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

#include "global.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

FrameBuffer *fb = NULL;
int window_width;
int window_height;

void fb_init(void) {
  if (!fb) {
    fb = malloc(sizeof(FrameBuffer));
    if (!fb)
      return;

    fb->data = malloc(2048);
    if (!fb->data) {
      free(fb);
      fb = NULL;
      return;
    }

    fb->capacity = 2048;
  }

  fb->len = 0;
}

void init_miamore_opts(const MiamoreOptions opts) {
  init = true;
  calc_window_size();
  fb_init();

  if (opts.should_clear) {
    request_screen(clear_origin_t);
  } else {
    snprintf(error_buf, sizeof(error_buf), "error\n");
    write_error(error_buf);
  }
}

void check_init(void) {
  if (!init) {
    snprintf(error_buf, sizeof(error_buf), "miamore not initialised");
    write_error(error_buf);
  } else {
    return;
    ;
  }
}

void write_error(char *error) {
  printf("[error] %s\n", error);
  exit(1);
}

// miamore functions
void(manage_cursor)(cursor_t cursor, position_t position) {
  switch (cursor) {
  case hide:
    request_cursor(hide);
    break;
  case show:
    request_cursor(show);
    break;
  case move:
    request_cursor(move, ((position_t){position.x, position.y}));
    break;
  }
}
