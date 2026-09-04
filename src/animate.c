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
#include <time.h>

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

long long get_time_ns(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

void animation_render(char **animation, unsigned int fps,
                      unsigned int duration) {

  if (NULL == animation) {
    draw_text_error(__PRETTY_FUNCTION__, "cannot animate this (NULL).", 1);
    return;
  }

  unsigned int num_frames = 0;
  while (animation[num_frames] != NULL) {
    num_frames++;
  }

  if (num_frames == 0) {
    draw_text_error(__PRETTY_FUNCTION__, "Animation array is empty!", 1);
    return;
  }

  long long duration_ns = (long long)duration * 1000000000LL;
  long long frame_delay_ns = 1000000000LL / fps;

  long long anim_start_time = get_time_ns();

  while (1) {
    long long current_time = get_time_ns();
    long long total_elapsed_ns = current_time - anim_start_time;

    if (total_elapsed_ns >= duration_ns) {
      break;
    }

    int current_frame_index = (total_elapsed_ns / frame_delay_ns) % num_frames;
    char *current_frame = animation[current_frame_index];

    printf("\x1b[H\x1b[J");

    fflush(stdout);
    buf_append(fb, current_frame, strlen(current_frame));
    render_frame(fb);
    fflush(stdout);

    long long draw_time = get_time_ns() - current_time;
    long long sleep_ns = frame_delay_ns - draw_time;

    if (sleep_ns > 0) {
      struct timespec req = {.tv_sec = (time_t)(sleep_ns / 1000000000LL),
                             .tv_nsec = (long)(sleep_ns % 1000000000LL)};
      nanosleep(&req, NULL);
    }
  }

  fflush(stdout);
}
