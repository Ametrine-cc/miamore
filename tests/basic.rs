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

#[test]
fn basic() {
    // Initialize miamore
    // enable if resize management should be used: bool
    // enable verbose output from miamore for debug: bool
    miamore_init(true, true);

    miamore_settings(MiamoreSettings {
        clear_on_reload: true,
        clear_on_startup: true,
        full_canvas_mode: false,
    });

    let c = input(input_mode::Short);
    println!("char: {}", c);
}
