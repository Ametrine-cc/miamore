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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;

/* KITTY Frames (full) */

const char **kitty_frames[] = {
    /* Frame 1: Neutral */
    (const char *[]){" /\\_/\\", "( o.o )", " > ^ <", NULL},

    /* Frame 2: Blink */
    (const char *[]){" /\\_/\\", "( -.- )", " > ^ <", NULL},

    /* Frame 3: Wink & Tail */
    (const char *[]){" /\\_/\\", "( ~.o ) ~", " > ^ <", NULL},

    NULL};

extern pthread_mutex_t stdout_mutex;

long long get_time_ns(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

typedef struct {
  pthread_t thread;
  volatile int running;
  const char ***animation;
  unsigned int fps;
  int x;
  int y;
  colors_t color;
  pthread_mutex_t pos_mutex; // Protects dynamic position updates
} anim_worker_t;

// Call this from the main thread if you move the animation anchor
// void update_animation_pos(void *handle, int new_x, int new_y) {
// if (!handle)
// return;
// anim_worker_t *worker = (anim_worker_t *)handle;

// pthread_mutex_lock(&worker->pos_mutex);
// worker->x = new_x;
// worker->y = new_y;
// pthread_mutex_unlock(&worker->pos_mutex);
// }

void *animation_render(void *arg) {
  anim_worker_t *worker = (anim_worker_t *)arg;

  if (worker == NULL || worker->animation == NULL)
    return NULL;

  unsigned int num_frames = 0;

  while (worker->animation[num_frames] != NULL) {
    num_frames++;
  }

  if (num_frames == 0)
    return NULL;

  long long frame_delay_ns = 1000000000LL / (worker->fps ? worker->fps : 1);
  long long start_time = get_time_ns();

  while (worker->running) {
    long long current_time = get_time_ns();
    long long total_elapsed_ns = current_time - start_time;
    int current_frame_index = (total_elapsed_ns / frame_delay_ns) % num_frames;

    if (worker->animation[current_frame_index] == NULL) {
      break;
    }

    pthread_mutex_lock(&worker->pos_mutex);
    int draw_x = worker->x;
    int draw_y = worker->y;
    pthread_mutex_unlock(&worker->pos_mutex);

    pthread_mutex_lock(&stdout_mutex);

    buf_append(fb, "\0337", 2);

    for (int l = 0; worker->animation[current_frame_index][l] != NULL; l++) {
      manage_cursor(move, ((position_t){.x = draw_x, .y = draw_y + l}));

      char *color = give_fg_color(worker->color);
      buf_append(fb, color, strlen(color));
      render_frame(fb);

      const char *current_line = worker->animation[current_frame_index][l];

      if (current_line == NULL)
        continue;

      buf_append(fb, current_line, strlen(current_line));
    }

    buf_append(fb, "\033[0m", 4);
    buf_append(fb, "\0338", 2);

    render_frame(fb);
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
  const char ***target_frames = opts.frames;

  if (!target_frames && opts.preset != PRESET_NONE) {
    switch (opts.preset) {
    case KITTY:
      target_frames = kitty_frames;
    case PRESET_NONE:
      break;
    }
  }

  anim_worker_t *worker = malloc(sizeof(anim_worker_t));
  if (!worker)
    return 0;

  worker->running = 1;
  worker->animation = target_frames;
  worker->fps = opts.fps;
  worker->x = opts.position.x;
  worker->y = opts.position.y;
  worker->color = opts.color;

  if (pthread_create(&worker->thread, NULL, animation_render, worker) != 0) {
    free(worker);
    return NULL;
  }

  wait_for(MS(0.02));

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
