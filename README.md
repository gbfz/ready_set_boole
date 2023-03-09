# ready_set_boole: overview of set theory

This is an implementation of a series of exercises at [42](https://42.fr/en/homepage/) focused on boolean algebra and set theory.

### Exercises briefly
  - bitwise operations
  - boolean functions
  - boolean formulas normalization (negation and conjunction forms)
  - truth table generation
  - operations on sets of variables or data
  - Hilbert curve manipulation

A tiny abstract syntax tree library found in the **ast** directory is used for parsing boolean formulas given in reverse Polish notation.

Definitions of exercises can be found in the __en.subject.pdf__ file.

### Installation
[meson](https://mesonbuild.com/) and [ninja](https://ninja-build.org/) are required for building. Once you get them, run **meson setup build** in project root, and a build directory will be configured. You can run **meson compile** there or...

### Testing
**Catch2** is used for testing. To test everything, run **meson test** in the build directory. To test exercises individually, just run binaries found in their respective directories in **build**.
