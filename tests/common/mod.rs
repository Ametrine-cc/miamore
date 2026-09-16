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

use miamore::*;

pub fn setup() {
    // Init miamore
    init_miamore(true, true, true);

    manage_keys(keys_t::disable);

    // Use debug
    debug(
        DebugType::tui,
        Some(DebugOptions {
            function: c"test".as_ptr(),
            error: c"This is an example of a debug error".as_ptr(),
        }),
    );

    // Wait for 2 seconds
    wait_for_seconds(2.0);

    // Clear screen
    clear_origin();
}

pub fn close() {
    close_miamore();

    debug(
        DebugType::console,
        Some(DebugOptions {
            function: c"test_2".as_ptr(),
            error: c"This is an example of a debug error through the console raw with printf()"
                .as_ptr(),
        }),
    );

    wait_for_seconds(2.0);
}
