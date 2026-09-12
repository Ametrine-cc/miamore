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
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

DrawCmd *g_cmds = NULL;
size_t g_cmd_count = 0;
size_t g_cmd_capacity = 0;

void buf_append(FrameBuffer *fb, const char *str, size_t len) {
  if (fb->len + len >= fb->capacity) {
    size_t new_cap = fb->capacity == 0 ? 1024 : fb->capacity * 2;
    while (new_cap <= fb->len + len)
      new_cap *= 2;
    fb->data = realloc(fb->data, new_cap);
    fb->capacity = new_cap;
  }
  memcpy(fb->data + fb->len, str, len);
  fb->len += len;
}

void render_frame(void) {
  fb.len = 0;

  struct winsize ws;
  int cols = 80, rows = 24;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
    cols = ws.ws_col;
    rows = ws.ws_row;
  }

  const char *clear_home = "\x1b[2J\x1b[H";
  buf_append(&fb, clear_home, strlen(clear_home));

  for (size_t i = 0; i < g_cmd_count; i++) {
    DrawCmd *cmd = &g_cmds[i];
    char temp[64];

    if (cmd->type == CMD_MOVE) {
      int n = snprintf(temp, sizeof(temp), "\x1b[%d;%dH", cmd->y, cmd->x);
      if (n > 0)
        buf_append(&fb, temp, (size_t)n);
    } else if (cmd->type == CMD_TEXT) {
      if (cmd->text)
        buf_append(&fb, cmd->text, strlen(cmd->text));
    } else if (cmd->type == CMD_BOX) {
      int box_w = (cmd->w > 0) ? cmd->w : (cols - cmd->x);
      int box_h = (cmd->h > 0) ? cmd->h : (rows - cmd->y);

      for (int r = cmd->y; r < cmd->y + box_h && r <= rows; r++) {
        int n = snprintf(temp, sizeof(temp), "\x1b[%d;%dH", r, cmd->x);
        buf_append(&fb, temp, (size_t)n);

        if (r == cmd->y || r == cmd->y + box_h - 1) {
          buf_append(&fb, "+", 1);
          for (int c = 0; c < box_w - 2; c++)
            buf_append(&fb, "-", 1);
          buf_append(&fb, "+", 1);
        } else {
          buf_append(&fb, "|", 1);
          int n2 = snprintf(temp, sizeof(temp), "\x1b[%d;%dH", r,
                            cmd->x + box_w - 1);
          buf_append(&fb, temp, (size_t)n2);
          buf_append(&fb, "|", 1);
        }
      }
    }
  }

  if (fb.len > 0) {
    write(STDOUT_FILENO, fb.data, fb.len);
  }
}
