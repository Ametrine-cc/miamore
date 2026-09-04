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

#include "include/miamore.h"
#include <stdio.h>

static char *cat_frames[] = {
    /* Frame 1: Neutral */
    " /\\_/\\ \n"
    "( o.o )\n"
    " > ^ < ",

    /* Frame 2: Blink */
    " /\\_/\\ \n"
    "( -.- )\n"
    " > ^ < ",

    /* Frame 3: Wink & Tail */
    " /\\_/\\ \n"
    "( ~.o ) ~\n"
    " > ^ < ",

    NULL};

char **load_preset_frames(animation_preset_t preset) {
  switch (preset) {
  case KITTY:
    return cat_frames;
  case PRESET_NONE:
    return NULL;
  }
}

char **animate_impl(AnimationOptions opts) {
  char **target_frames = opts.frames;

  if (!target_frames && opts.preset != PRESET_NONE) {
    target_frames = load_preset_frames(opts.preset);
  }

  return target_frames;
}

void animation_render(char **animation, fps_t fps) {
  if (NULL == animation) {
    draw_error(__PRETTY_FUNCTION__,
               "cannot animate this.\nPlease check codebase as returned NULL!",
               1);
  }
  printf("%d\n", fps);
  printf("%s", animation[1]);
}
