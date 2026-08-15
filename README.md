# miamore
Making TUI applications simply

`miamore` is a library for `C` allowing you to make TUI apps simply.

`miamore` exists as a ncurses replacement(not drop in, syntax is very different) allowing developers to make TUI applications much easier with more features.

## Installing miamore:

### System
*   `Linux` (or `UNIX` system).
*   `clang` (to compile the code).
*   `make` (automate build and install process).

Install `miamore` from source:

```bash
# All distrobutions
git clone https://github.com/Ametrine-cc/miamore.git
cd miamore

# --- Building and installing miamore
sudo make clean # Remove any miamore files that may already exist

make # run the make command to build everything initially then install
sudo make install

# --- To uninstall run the uninstall command instead ---
sudo make uninstall
```

## Using kazmai:

When using `miamore`, the library must be linked during compilation. You can do this in two ways:

In `clang` or `gcc`:

```bash
# --- Include the kazmailib for compilation ---
clang src/PROJECT_NAME -lmiamore -o PROJECT_NAME
```

The example shows `clang` but can be swapped out interchangeably with `gcc`.

In `cmake`:

```bash
# --- Dependencies ---
find_library(MIAMORE_PATH NAMES miamore)

# --- Check if it was actually found ---
if(NOT MIAMORE_PATH)
  message(FATAL_ERROR "miamore not found! Did you install with 'sudo/doas make install' to install the library?")
endif()

target_link_libraries(PROJECT_NAME PRIVATE ${MIAMORE_PATH})
```

Replace `"PROJECT_NAME"` with your project name. All code presented is drag-and-droppable.

More information can be found on the [Ametrine Foundation Documentation website](https://docs.ametrine.cc/libraries/miamore)

## How to contribute?

We welcome contributions from the community to help improve `miamore`! Whether it's reporting bugs, suggesting new features, or submitting code changes, your help is valuable.

### Reporting Bugs

If you find a bug, please help us by reporting it on the [GitHub Issues page](https://github.com/Ametrine-cc/Kamakazi/issues). When reporting a bug, please include:

*   A clear and concise description of the bug.
*   Steps to reproduce the behavior.
*   Expected behavior vs. actual behavior.
*   Any error messages or logs.
*   Your operating system and compiler version.

### Suggestions

Do you have an idea for a new feature or an improvement to an existing one? We'd love to hear about it! Please open an issue on the [GitHub Issues page](https://github.com/Ametrine-cc/miamore/issues) and:

*   Clearly describe the proposed feature or enhancement.
*   Explain the problem it solves or the use case it addresses.
*   (Optional) Provide any thoughts on how it might be implemented.

Thank you for helping to make `miamore` better!

## Credits:

*   Lead Developer - [Noticxs](https://github.com/Noticxs)

## License

This project is dual-licensed under the **GNU Affero General Public License v3.0 (AGPL-3.0)** and a **Commercial License**.

- **Open Source / Non-Commercial Use:** You are free to use, modify, and distribute this software under the terms of the AGPL-3.0 license. See the `LICENSE` file for details.
- **Commercial / Proprietary Use:** If you wish to use this software in a closed-source project, embed it into proprietary software, or use it without the copyleft restrictions of the AGPL-3.0, you must acquire a commercial license.

<!-- To purchase a commercial license or discuss custom licensing terms, please contact [business@ametrine.cc] or visit [ametrine.cc/licensing]. -->
To purchase a commercial license or discuss custom licensing terms, please contact [business@ametrine.cc].
