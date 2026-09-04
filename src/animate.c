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

char **animate_impl(AnimationOptions opts) {
  char **target_frames = opts.frames;

  if (!target_frames && opts.preset != PRESET_NONE) {
    // target_frames = load_preset_frames(opts.preset);
    printf("%d\n", opts.preset);
  }

  /* Handle animation rendering / generation logic */
  return target_frames;
}

// void animation_opts(AnimationPresets opts, char **frames) {}
