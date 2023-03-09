# ready_set_boole
### [42](https://42.fr/en/homepage/)'s introduction to boolean algebra


This is an implementation of a series of exercises at 42 that introduces students to boolean logic and set theory.
Their definitions can be found in the __en.subject.pdf__ file.

Several of the exercises employ mathematical *bit twiddling hacks™*.
Others are aimed at logical calculations. They employ a tiny abstract syntax tree library found in **ast** directory and use it to generate truth tables, evaluate sets, and produce powersets.

Exercises are implemented using **C++20**, so you'll need the latest edition of your favorite compiler.

### Installation
[**meson**](https://mesonbuild.com/) and [**ninja**](https://ninja-build.org/) are required for building. Once you get them, run **meson setup build** in project root directory, and then **meson compile** in the generated build directory.

### Testing
**Catch2** is used for testing. To test everything, run **meson test** in the build directory. To test exercises individually, just run binaries found in their respective directories in **build**.
