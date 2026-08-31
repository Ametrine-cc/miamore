use std::env;
use std::fs;
use std::path::PathBuf;

fn main() {
    let current_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    println!("cargo:rustc-link-search=native={}/build", current_dir);
    println!("cargo:rustc-link-lib=static=miamore");

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
