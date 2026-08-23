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
#include <stdio.h>

typedef struct ASCIIEscapeCodes {
  const char *clear;
  const char *clear_origin;
  const char *reset_styles;
  const char *show_cursor;
  const char *hide_cursor;
} ASCIIEscapeCodes;

static ASCIIEscapeCodes aes_instance = {.clear = "\x1b[2J",
                                        .clear_origin = "\x1b[2J \x1b[1;1H",
                                        .reset_styles = "\x1b[0m",
                                        .show_cursor = "\x1b[?25h",
                                        .hide_cursor = "\x1b[?25l"};

static ASCIIEscapeCodes *aec = &aes_instance;

void request_screen(screen_options screen) {
  check_init();
  fflush(stdout);

  switch (screen) {
  case reset:
    snprintf(temp_buf, sizeof(temp_buf), "%s", aec->reset_styles);
    buf_append(fb, temp_buf, sizeof(temp_buf));
    render_frame(fb);

    break;
  case clear:
    snprintf(temp_buf, sizeof(temp_buf), "%s", aec->clear);
    buf_append(fb, temp_buf, sizeof(temp_buf));
    render_frame(fb);

    break;
  case clear_origin:
    snprintf(temp_buf, sizeof(temp_buf), "%s", aec->clear_origin);
    buf_append(fb, temp_buf, sizeof(temp_buf));
    render_frame(fb);

    break;
  }
}
