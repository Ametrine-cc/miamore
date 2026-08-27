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
#include "include/miamore.h"
#include <stdio.h>
#include <string.h>

typedef struct ASCIIEscapeCodes {
  const char *clear;
  const char *origin;
  const char *reset_styles;
  const char *show_cursor;
  const char *hide_cursor;
} ASCIIEscapeCodes;

static ASCIIEscapeCodes aes_instance = {.clear = "\x1b[2J",
                                        .origin = "\x1b[1;1H",
                                        .reset_styles = "\x1b[0m",
                                        .show_cursor = "\x1b[?25h",
                                        .hide_cursor = "\x1b[?25l"};

static ASCIIEscapeCodes *aec = &aes_instance;

void request_screen(screen_options screen) {
  check_init();
  fflush(stdout);

  switch (screen) {
  case reset_t:
    snprintf(temp_buf, sizeof(temp_buf), "%s", aec->reset_styles);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);

    break;
  case clear_t:
    snprintf(temp_buf, sizeof(temp_buf), "%s", aec->clear);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);

    break;
  case clear_origin_t:
    snprintf(temp_buf, sizeof(temp_buf), "%s", aec->clear);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);

    snprintf(temp_buf, sizeof(temp_buf), "%s", aec->origin);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);

    break;
  }
}

void show_cursor() {
  fflush(stdout);

  snprintf(temp_buf, sizeof(temp_buf), "%s", aec->show_cursor);
  buf_append(fb, temp_buf, strlen(temp_buf));
  render_frame(fb);
}

void hide_cursor() {
  fflush(stdout);

  snprintf(temp_buf, sizeof(temp_buf), "%s", aec->hide_cursor);
  buf_append(fb, temp_buf, strlen(temp_buf));
  render_frame(fb);
}

void move_cursor(int x, int y) {
  fflush(stdout);

  snprintf(temp_buf, sizeof(temp_buf), "\033[%d;%dH", y + 1, x + 1);
  buf_append(fb, temp_buf, strlen(temp_buf));
  render_frame(fb);
}

void(request_cursor)(cursor_t cursor, position_t position) {
  check_init();
  fflush(stdout);

  switch (cursor) {
  case hide:
    hide_cursor();
    break;
  case show:
    show_cursor();
    break;
  case move:
    move_cursor(position.x, position.y);
    break;
  }
}

void draw_box(int width, int height) {
  if (!height || !width)
    return;

  manage_cursor(move, ((position_t){1, 1}));
  fflush(stdout);
  for (int x = 0; x < width; x++)
    buf_append(fb, "-", 1);
  render_frame(fb);

  for (int y = 2; y < height; y++) {

    // Left wall
    manage_cursor(move, ((position_t){1, y}));
    fflush(stdout);
    buf_append(fb, "|", 1);
    render_frame(fb);

    // Right wall
    manage_cursor(move, ((position_t){width, y}));
    fflush(stdout);
    buf_append(fb, "|", 1);
    render_frame(fb);
  }

  // Bottom border
  manage_cursor(move, ((position_t){1, height}));
  fflush(stdout);
  for (int x = 0; x < width; x++)
    buf_append(fb, "-", 1);
  render_frame(fb);
}

void(request_draw)(shape_t shape, dimensions_t dimentions, position_t position,
                   theme_t theme) {
  check_init();
  fflush(stdout);

  // remove unused var error during compilation
  (void)(dimentions);
  (void)(position);
  (void)(theme);

  char tx[512];

  switch (shape) {
  case rect:
    draw_box(dimentions.width, dimentions.height);
    break;
  default:
    break;
  }
}
