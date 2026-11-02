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
#include "include/miamore_internal.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Set some default values

// Set window height and width
int window_height = -1;
int window_width = -1;

// Set cursor x and y
unsigned int cursor_x = 0;
unsigned int cursor_y = 0;

bool verbose = false;

void miamore_init(bool manage_resize_reload, bool enable_verbose) {
  char buffer[MAX_BUFFER_SIZE];
  verbose = enable_verbose;

  // Get window size, width(row) and height(col)
  if (verbose) {
    snprintf(buffer, MAX_BUFFER_SIZE, "window_width:\t%d",
             get_window_size()[0]);
    return_debug(__FUNCTION__, buffer);

    snprintf(buffer, MAX_BUFFER_SIZE, "window_height:\t%d",
             get_window_size()[1]);
    return_debug(__FUNCTION__, buffer);
  }

  if (manage_resize_reload) {
    // Create resize thread
    pthread_t managed_resize_thread;

    // Check for window resize
    if (pthread_create(&managed_resize_thread, NULL, check_for_window_resize,
                       NULL) != 0) {
      perror("Failed to create thread");
      exit(1);
    }
    pthread_detach(managed_resize_thread);
  }
}

void miamore_settings_opts(MiamoreSettings settings) {
  if (settings.clear_on_reload) {
    return_debug(__FUNCTION__, "clear on reload");
  }
  if (settings.clear_on_startup) {
    return_debug(__FUNCTION__, "clear on startup");
  }
  if (settings.full_canvas_mode) {
    return_debug(__FUNCTION__, "full canvas mode");
  }
}
