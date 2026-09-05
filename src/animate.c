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
#include <pthread.h>
// #include <stdio.h>
#include <string.h>
#include <time.h>

pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;

static char *kitty_frames[] = {
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
    return kitty_frames;
  case PRESET_NONE:
    return NULL;
  }
}

void *animation_render() {

  if (NULL == animation) {
    draw_text_error(__PRETTY_FUNCTION__, "cannot animate this (NULL).", 1);
    return;
  }

  int frame = 0;
}

void animate_impl(AnimationOptions opts) {
  char **target_frames = opts.frames;

  pthread_t anim_thread;

  if (!target_frames && opts.preset != PRESET_NONE) {
    target_frames = load_preset_frames(opts.preset);
  }

  pthread_create(&anim_thread, NULL, animation_render, NULL);
}

long long get_time_ns(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}
