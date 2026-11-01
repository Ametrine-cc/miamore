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

mod common;

#[test]
fn animation() {
    common::setup();

    // Drawing border
    draw_border("Animation test", theme_t::thick_l);

    // Managing cursor
    manage_cursor(cursor_t::move_, Some(position_t { x: 5, y: 5 }));
    manage_cursor(cursor_t::show, None);

    // Setting foreground color
    set_fg(colors_t::blue);

    // Drawing text
    draw_text("Hello,");
    draw_text(" World!\n");

    // Drawing shapes
    draw_shape(
        shape_t::rect,
        ShapeOptions {
            theme: theme_t::double_l,
            dimensions: dimensions_t {
                width: 26,
                height: 12,
            },
            position: position_t { x: 5, y: 12 },
        },
    );

    set_fg(colors_t::white);

    // Animation
    // You should not use manage_cursor() to set the position of an animation

    let anim = start_animation(
        None, // Some(&data) // Pass in custom frames
        Some(animation_preset_t::KITTY),
        4,
        position_t { x: 20, y: 4 },
        colors_t::green,
    );

    set_fg(colors_t::yellow);

    manage_cursor(cursor_t::move_, Some(position_t { x: 4, y: 4 }));
    draw_text("hiya");

    let mut runtime: bool = true;

    while runtime {
        let input = input();

        if input == b'q' as i32 {
            runtime = false;
        }
    }

    end_animation(anim);

    common::close();
}
