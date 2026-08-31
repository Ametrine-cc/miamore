// bindings/rust/miamore.rs

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

#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

use std::ffi::{CStr, CString};
use std::os::raw::c_char;

pub mod sys {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub use sys::{
    BorderOptions, MiamoreOptions, ShapeOptions, colors_t, cursor_t, dimensions_t, keys_t,
    position_t, seconds_t, shape_t, theme_t,
};

pub fn window_width() -> u32 {
    unsafe { sys::window_width }
}
pub fn window_height() -> u32 {
    unsafe { sys::window_height }
}
pub fn cursor_x() -> u32 {
    unsafe { sys::cursor_x }
}
pub fn cursor_y() -> u32 {
    unsafe { sys::cursor_y }
}

/// Core Window Functions
pub fn calc_window_size() {
    unsafe { sys::calc_window_size() }
}

pub fn clear() {
    unsafe { sys::clear() }
}

pub fn clear_origin() {
    unsafe { sys::clear_origin() }
}

pub fn init_miamore(should_clear: bool, disable_mouse: bool) {
    let opts = MiamoreOptions {
        should_clear,
        disable_mouse,
    };
    unsafe { sys::init_miamore_opts(opts) }
}

/// Input
pub fn input() -> i32 {
    unsafe { sys::input() as i32 }
}

pub fn input_ex() -> String {
    unsafe {
        let ptr = sys::input_ex();
        if ptr.is_null() {
            return String::new();
        }
        CStr::from_ptr(ptr).to_string_lossy().into_owned()
    }
}

pub fn wait_for_seconds(s: f64) {
    unsafe { sys::wait_for(s as seconds_t) }
}

pub fn wait_for_ms(m: f64) {
    unsafe { sys::wait_for((m / 1000.0) as seconds_t) }
}

/// Keyboard and Cursor
pub fn manage_keys(keyboard: keys_t) {
    unsafe { sys::manage_keys(keyboard) }
}

pub fn manage_cursor(cursor: cursor_t, position: Option<position_t>) {
    let pos = position.unwrap_or(position_t { x: 0, y: 0 });
    unsafe { sys::manage_cursor(cursor, pos) }
}

/// Drawing Functions
pub fn draw_text(text: &str) {
    let c_text = CString::new(text).expect("String contained null bytes");
    unsafe { sys::draw_text(c_text.as_ptr()) }
}

pub fn draw_shape(shape: shape_t, opts: ShapeOptions) {
    unsafe { sys::draw_shape_opts(shape, opts) }
}

pub fn draw_border(text: &str, theme: theme_t) {
    let c_text = CString::new(text).expect("String contained null bytes");

    let opts = BorderOptions {
        text: c_text.as_ptr() as *mut c_char,
        theme,
    };

    unsafe { sys::draw_border_opts(opts) }
}

/// Color Functions
pub fn give_color(_color: colors_t) -> String {
    unsafe {
        let ptr = sys::give_color(_color);
        if ptr.is_null() {
            return String::new();
        }
        CStr::from_ptr(ptr).to_string_lossy().into_owned()
    }
}

pub fn set_fg(color: colors_t) {
    unsafe {
        sys::set_fg(color);
    }
}

pub fn set_bg(color: colors_t) {
    unsafe {
        sys::set_bg(color);
    }
}

/// Test function
pub fn test(s: &str) {
    let c_string = CString::new(s).expect("String contained null bytes");
    unsafe {
        sys::test(c_string.as_ptr() as *mut c_char);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_miamore_example() {
        init_miamore(true, true);

        manage_keys(keys_t::disable);

        draw_border("!Rust test!", theme_t::thick_l);

        manage_cursor(cursor_t::move_, Some(position_t { x: 5, y: 5 }));
        manage_cursor(cursor_t::show, None);

        // setting foreground color
        set_fg(colors_t::blue);
        // let ptr = give_color(colors_t::green);
        // draw_text(&ptr);

        draw_text("Hello,");
        draw_text(" World!\n");

        //
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

        wait_for_seconds(8.0);
        clear_origin();
    }
}
