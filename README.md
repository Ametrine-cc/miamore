# miamore
Making TUI applications simply

`miamore` is a library for `C` allowing you to make TUI apps simply.

`miamore` exists as a ncurses replacement(not drop in, syntax is very different) allowing developers to make TUI applications much easier with more features.
miamore adds native 24-bit colors and the support to make animations directly in the library without having to add extra boilerplate in your main codebase.
miamore also streamlines some processes about normal nurses such as the ability to create shapes with our 'draw()' function.
More information can be found on the [Ametrine Foundation Documentation website](https://docs.ametrine.cc/libraries/miamore)

## Installing miamore:

### Dependencies

*   `Linux` (other `UNIX-Like` or `UNIX` system have not been tested).
*   `clang` (to compile the code).
*   `make` (automate build and install process).

Install `miamore` from source:

### Cloning miamore
```bash
# All distrobutions
git clone https://github.com/Ametrine-cc/miamore.git
cd miamore

```

### Building miamore
```bash
# building the .a lib
make static

# building the .so library
make dynamic

# building rust bindings
# needs either static or dynamic library to be built before hand
make rust-build

# building both .a, .so and the rust bindings
make all
```

### Installing miamore
```bash
# To use these commands use superuser privilages (sudo or doas)
# To install the library on your system
sudo make install

# To uninstall run the uninstall command instead
sudo make uninstall
```

Examples can be found in `examples/example.c` and by running `make rust-test` after compilation

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
