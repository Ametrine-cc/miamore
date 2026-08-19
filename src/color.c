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

#include "miamore.h"
#include <stdio.h>
#include <string.h>

static colors_t fg_colors_instance = {.red = "\x1b[38;2;231;76;60m",
                                      .orange = "\x1b[38;2;230;126;34m",
                                      .yellow = "\x1b[38;2;241;196;15m",
                                      .green = "\x1b[38;2;46;204;113m",
                                      .blue = "\x1b[38;2;52;152;219m",
                                      .pink = "\x1b[38;2;232;67;147m",
                                      .purple = "\x1b[38;2;142;68;173m",
                                      .cyan = "\x1b[38;2;0;206;201m",
                                      .magenta = "\x1b[38;2;253;121;168m",
                                      .black = "\x1b[38;2;0;0;0m",
                                      .white = "\x1b[38;2;255;255;255m",
                                      .reset = "\x1b[0m"};

static colors_t bg_colors_instance = {.red = "\x1b[48;2;231;76;60m",
                                      .orange = "\x1b[48;2;230;126;34m",
                                      .yellow = "\x1b[48;2;241;196;15m",
                                      .green = "\x1b[48;2;46;204;113m",
                                      .blue = "\x1b[48;2;52;152;219m",
                                      .pink = "\x1b[48;2;232;67;147m",
                                      .purple = "\x1b[48;2;142;68;173m",
                                      .cyan = "\x1b[48;2;0;206;201m",
                                      .magenta = "\x1b[48;2;253;121;168m",
                                      .black = "\x1b[48;2;0;0;0m",
                                      .white = "\x1b[48;2;255;255;255m"};

static colors_t *fg_colors = &fg_colors_instance;
static colors_t *bg_colors = &bg_colors_instance;

void set_fg(colors color) {
  fflush(stdout);

  switch (color) {
  case COLOR_RED:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.red);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_ORANGE:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.orange);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_YELLOW:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.yellow);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_GREEN:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.green);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_BLUE:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.blue);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_PINK:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.pink);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_PURPLE:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.purple);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_CYAN:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.cyan);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_MAGENTA:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.magenta);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_BLACK:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.black);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_WHITE:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.white);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  case COLOR_RESET:
    snprintf(temp_buf, sizeof(temp_buf), "%s", fg_colors_instance.reset);
    buf_append(fb, temp_buf, strlen(temp_buf));
    render_frame(fb);
    break;
  }
}
