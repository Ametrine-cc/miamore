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

// use std::{
// ffi::{CStr, CString, c_char, c_void},
// ptr::{self, null, null_mut},
// };

pub mod sys {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

// pub use sys::{
// AnimationOptions, BorderOptions, DebugOptions, DebugType, MiamoreOptions, ShapeOptions,
// animation_preset_t, colors_t, cursor_t, dimensions_t, keys_t, position_t, seconds_t, shape_t,
// theme_t,
// };

/// Functions for terminal window resizing
pub fn miamore_init() {
    unsafe { sys::miamore_init() }
}
