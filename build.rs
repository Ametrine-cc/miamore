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

use std::env;
use std::fs;
use std::path::PathBuf;
use std::process::Command;

fn main() {
    let current_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    let status = Command::new("make")
        .arg("static")
        .status()
        .expect("Failed to execute `make`.");

    if !status.success() {
        panic!("`make` failed to build the native miamore C library.");
    }

    println!("cargo:rustc-link-search=native={}/build", current_dir);
    println!("cargo:rustc-link-lib=static=miamore");

    println!("cargo:rerun-if-changed=Makefile");
    println!("cargo:rerun-if-changed=src/include/miamore.h");
    println!("cargo:rerun-if-changed=build/libmiamore.a");

    let bindings = bindgen::Builder::default()
        .header("src/include/miamore.h")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        .default_enum_style(bindgen::EnumVariation::Rust {
            non_exhaustive: true,
        })
        .generate()
        .expect("Unable to generate bindings");

    let bindings_str = bindings.to_string();
    let patched_bindings = bindings_str.replace("extern \"C\" {", "unsafe extern \"C\" {");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    fs::write(out_path.join("bindings.rs"), patched_bindings).expect("Couldn't write bindings!");
}
