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

// #include "global.h"
#include "include/miamore.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;

static char *kitty_frames[] = {
    /* Frame 1: Neutral */
    " /\\_/\\ \033[1B\033[7D( o.o )\033[1B\033[7D > ^ < ",

    /* Frame 2: Blink */
    " /\\_/\\ \033[1B\033[7D( -.- )\033[1B\033[7D > ^ < ",

    /* Frame 3: Wink & Tail */
    " /\\_/\\ \033[1B\033[7D( ~.o ) ~\033[1B\033[9D > ^ < ",

    NULL};

char **load_preset_frames(animation_preset_t preset) {
  switch (preset) {
  case KITTY:
    return kitty_frames;
  case PRESET_NONE:
    return NULL;
  }

  return NULL;
}

extern pthread_mutex_t stdout_mutex;

typedef struct {
  pthread_t thread;
  volatile int running;
  char **animation;
  unsigned int fps;
  unsigned int duration;
} anim_worker_t;

long long get_time_ns(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

void *animation_render(void *arg) {
  anim_worker_t *worker = (anim_worker_t *)arg;

  if (NULL == worker->animation) {
    draw_text_error(__PRETTY_FUNCTION__, "cannot animate this (NULL).", 1);
    free(worker);
    return NULL;
  }

  unsigned int num_frames = 0;
  while (worker->animation[num_frames] != NULL) {
    num_frames++;
  }

  if (num_frames == 0) {
    draw_text_error(__PRETTY_FUNCTION__, "Animation array is empty!", 1);
    free(worker);
    return NULL;
  }

  long long frame_delay_ns = 1000000000LL / (worker->fps ? worker->fps : 1);
  long long start_time = get_time_ns();

  while (worker->running) {
    long long current_time = get_time_ns();
    long long total_elapsed_ns = current_time - start_time;

    int current_frame_index = (total_elapsed_ns / frame_delay_ns) % num_frames;
    char *current_frame = worker->animation[current_frame_index];

    pthread_mutex_lock(&stdout_mutex);

    printf("\033[s");
    printf("%s", current_frame);
    printf("\033[u");

    fflush(stdout);

    pthread_mutex_unlock(&stdout_mutex);

    long long draw_time = get_time_ns() - current_time;
    long long remaining_sleep_ns = frame_delay_ns - draw_time;

    while (remaining_sleep_ns > 0 && worker->running) {
      long long chunk =
          remaining_sleep_ns > 10000000LL ? 10000000LL : remaining_sleep_ns;
      struct timespec req = {.tv_sec = 0, .tv_nsec = (long)chunk};
      nanosleep(&req, NULL);
      remaining_sleep_ns -= chunk;
    }
  }

  return NULL;
}

void *animate_impl(AnimationOptions opts) {
  char **target_frames = opts.frames;

  if (!target_frames && opts.preset != PRESET_NONE) {
    target_frames = load_preset_frames(opts.preset);
  }

  anim_worker_t *worker = malloc(sizeof(anim_worker_t));
  if (!worker)
    return 0;

  worker->running = 1;
  worker->animation = target_frames;
  worker->fps = opts.fps;

  if (pthread_create(&worker->thread, NULL, animation_render, worker) != 0) {
    free(worker);
    return NULL;
  }

  return (void *)worker;
}

void end_animation(void *handle) {
  if (!handle)
    return;

  anim_worker_t *worker = (anim_worker_t *)handle;

  worker->running = 0;
  pthread_join(worker->thread, NULL);
  free(worker);
}
