// bindings/rust/miamore.rs

#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

use std::ffi::{CStr, CString};
use std::os::raw::c_char;

pub mod sys {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub use sys::{
    BorderOptions, MiamoreOptions, ShapeOptions, cursor_t, dimensions_t, keys_t, position_t,
    seconds_t, shape_t, theme_t,
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

        draw_border("this is an example!", theme_t::thick_l);

        manage_cursor(cursor_t::move_, Some(position_t { x: 5, y: 5 }));
        manage_cursor(cursor_t::show, None);

        draw_text("Hello,");
        draw_text(" World!\n");

        manage_cursor(cursor_t::move_, Some(position_t { x: 5, y: 10 }));

        draw_shape(
            shape_t::rect,
            ShapeOptions {
                theme: theme_t::single_l,
                dimensions: dimensions_t {
                    width: 26,
                    height: 12,
                },
                position: position_t { x: 0, y: 0 },
            },
        );

        wait_for_seconds(8.0);
        clear_origin();
    }
}
