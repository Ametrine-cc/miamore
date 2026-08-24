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
#include <time.h>

void clear(void) { request_screen(clear_t); }

void clear_origin(void) { request_screen(clear_origin_t); }

void wait_for(seconds_t seconds) {
  if (seconds <= 0.0)
    return;

  struct timespec req;
  req.tv_sec = (time_t)seconds;
  req.tv_nsec = (double)((seconds - req.tv_sec) * 1e9);
  nanosleep(&req, NULL);
}
