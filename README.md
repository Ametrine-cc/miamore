# miamore
Making TUI applications simply

`miamore` is a library for `C` allowing you to make TUI apps simply.

`miamore` exists as a ncurses replacement(not drop in, syntax is very different) allowing developers to make TUI applications much easier with more features.

miamore adds native 24-bit colors and the support to make animations directly in the library without having to add extra boilerplate in your main codebase.

miamore also streamlines some processes about normal nurses such as the ability to create shapes with our 'draw()' function.

## Installing miamore:

### System
*   `Linux`
*   `clang` (to compile the code).
*   `make` (automate build and install process).

Install `miamore` from source:

```bash
# All distrobutions
git clone https://github.com/Ametrine-cc/miamore.git
cd miamore

# --- Building and installing miamore ---
sudo make clean # Remove any miamore files that may already exist

make # run the make command to build everything initially then install
sudo make install

# --- To uninstall run the uninstall command instead ---
sudo make uninstall
```

## Using miamore:

When using `miamore`, the library must be linked during compilation. You can do this in two ways:

In `clang` or `gcc`:

```bash
# --- Include the libmiamore.a for compilation ---
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

If you find a bug, please help us by reporting it on the [GitHub Issues page](https://github.com/Ametrine-cc/miamore/issues). When reporting a bug, please include:

*   A clear and concise description of the bug.
*   Steps to reproduce the behavior.
*   Expected behavior vs. actual behavior.
*   Any error messages or logs.
*   Your operating system and compiler version.

## Credits:

*   Lead Developer - [Noticxs](https://github.com/Noticxs)

## License

## Licensing
This project is licensed under the GNU Lesser General Public License v3.0 or later (LGPL-3.0-or-later) - see `LICENSE` and `LICENSE.LESSER` for details.

### Using this library in commercial/closed-source software
You can use `libyourname` in closed-source projects via dynamic linking (`.so`/`.dll`). If you modify `libyourname` directly, those modifications must be released under the LGPL.
