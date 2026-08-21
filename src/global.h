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
// included libraries

#ifndef GLOBAL_H
#define GLOBAL_H

#include "include/miamore.h"
#include <stddef.h>

// misc
static char temp_buf[512];
extern unsigned int current_position[2];

// framebuffer
typedef struct {
  char *data;
  size_t capacity;
  size_t len;
} FrameBuffer;

extern FrameBuffer *fb;
void check_fb(void);

void buf_append(FrameBuffer *fb, const char *str, size_t len);
void render_frame(FrameBuffer *fb);

// colors
typedef struct colors_t {
  const char *red;
  const char *orange;
  const char *yellow;
  const char *green;
  const char *blue;
  const char *pink;
  const char *purple;
  const char *cyan;
  const char *magenta;
  const char *black;
  const char *white;
  const char *reset;
} colors_t;

// global ASCII Escape Codes
typedef struct ASCIIEscapeCodes {
  const char *clear;
  const char *reset_styles;
  const char *show_cursor;
  const char *hide_cursor;
} ASCIIEscapeCodes;

static ASCIIEscapeCodes aes_instance = {.clear = "\x1b[2J",
                                        .reset_styles = "\x1b[0m",
                                        .show_cursor = "\x1b[?25h",
                                        .hide_cursor = "\x1b[?25l"};

static ASCIIEscapeCodes *aec = &aes_instance;

#endif // GLOBAL_H
