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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void buf_append(FrameBuffer *buf, const char *str, size_t len) {
  if (!buf || !buf->data || !str)
    return;

  if (buf->len + len > buf->capacity) {
    size_t new_cap = (buf->capacity == 0) ? 1024 : (buf->len + len) * 2;
    char *new_data = realloc(buf->data, new_cap);
    if (!new_data)
      return;

    buf->data = new_data;
    buf->capacity = new_cap;
  }
  memcpy(buf->data + buf->len, str, len);
  buf->len += len;
}

void render_frame(FrameBuffer *buf) {
  if (!buf || buf->len == 0)
    return;

  write(STDOUT_FILENO, buf->data, buf->len);
  buf->len = 0;
}
