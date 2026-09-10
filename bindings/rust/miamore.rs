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

use std::{
    ffi::{CStr, CString, c_char, c_void},
    ptr::{self, null, null_mut},
};

pub mod sys {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub use sys::{
    AnimationOptions, BorderOptions, DebugOptions, DebugType, MiamoreOptions, ShapeOptions,
    animation_preset_t, colors_t, cursor_t, dimensions_t, keys_t, position_t, seconds_t, shape_t,
    theme_t,
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

pub fn init_miamore(should_clear: bool, disable_mouse: bool, resize: bool) {
    let opts = MiamoreOptions {
        should_clear,
        disable_mouse,
        resize,
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
pub fn give_fg_color(_color: colors_t) -> String {
    unsafe {
        let ptr = sys::give_fg_color(_color);
        if ptr.is_null() {
            return String::new();
        }
        CStr::from_ptr(ptr).to_string_lossy().into_owned()
    }
}

pub fn give_bg_color(_color: colors_t) -> String {
    unsafe {
        let ptr = sys::give_bg_color(_color);
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

/// added in v0.2.1

/// Debug Function

pub fn debug(debug_type: DebugType, debug_options: Option<DebugOptions>) {
    let opts = debug_options.unwrap_or(DebugOptions {
        function: c"".as_ptr(),
        error: c"".as_ptr(),
    });

    unsafe {
        sys::debug_opts(debug_type, opts);
    }
}

/// Animation Support

struct AnimationContext {
    c_handle: *mut c_void,
    frames_ptr: *mut *mut *const i8,
}

pub fn start_animation(
    frames: Option<&[Vec<String>]>,
    preset: Option<animation_preset_t>,
    fps: u32,
    position: position_t,
    color: colors_t,
) -> *mut c_void {
    let frames_ptr = match frames {
        Some(rust_frames) => {
            let mut c_rows: Vec<*mut *const i8> = rust_frames
                .iter()
                .map(|row| {
                    let mut c_strings: Vec<*const i8> = row
                        .iter()
                        .map(|s| {
                            let cstring = CString::new(s.as_str()).expect("Null byte found");
                            cstring.into_raw() as *const i8
                        })
                        .collect();

                    c_strings.push(null());
                    let c_strings_boxed = c_strings.into_boxed_slice();
                    Box::into_raw(c_strings_boxed) as *mut *const i8
                })
                .collect();

            c_rows.push(null_mut());
            let c_rows_boxed = c_rows.into_boxed_slice();
            Box::into_raw(c_rows_boxed) as *mut *mut *const i8
        }
        None => null_mut(),
    };

    let actual_preset = preset.unwrap_or(animation_preset_t::PRESET_NONE);

    let opts = AnimationOptions {
        frames: frames_ptr,
        preset: actual_preset,
        fps,
        position,
        color,
    };

    let c_handle = unsafe { sys::animate_impl(opts) };

    let context = Box::new(AnimationContext {
        c_handle,
        frames_ptr,
    });

    Box::into_raw(context) as *mut c_void
}

pub fn end_animation(handle: *mut c_void) {
    if handle.is_null() {
        return;
    }

    unsafe {
        let context = Box::from_raw(handle as *mut AnimationContext);

        sys::end_animation(context.c_handle);

        let frames_ptr = context.frames_ptr;
        if !frames_ptr.is_null() {
            let mut row_count = 0;

            while !(*frames_ptr.add(row_count)).is_null() {
                let row_ptr = *frames_ptr.add(row_count);
                let mut col_count = 0;

                while !(*row_ptr.add(col_count)).is_null() {
                    let c_str_ptr = *row_ptr.add(col_count) as *mut i8;
                    let _ = CString::from_raw(c_str_ptr);
                    col_count += 1;
                }

                let row_slice = ptr::slice_from_raw_parts_mut(row_ptr, col_count + 1);
                let _ = Box::from_raw(row_slice);

                row_count += 1;
            }

            let grid_slice = ptr::slice_from_raw_parts_mut(frames_ptr, row_count + 1);
            let _ = Box::from_raw(grid_slice);
        }
    }
}

/// close miamore
pub fn close_miamore() {
    unsafe {
        sys::close_miamore();
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
    fn miamore_test() {
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

        // Drawing border
        draw_border("!Rust test!", theme_t::thick_l);

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

        // let data = vec![vec![String::from("snake")]];
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
}
