# Secure C

This directory contains small, focused examples for learning secure C patterns.
Each lesson is kept as a separate implementation, test, and demo so the project
stays easy to read and review one concept at a time.

## Lessons

- `safe_integer`: parse signed decimal text safely into `int32_t` and reject
  malformed or out-of-range input.
- `safe_copy`: copy a string into a fixed-size destination only when the full
  source fits, returning a clear failure when the buffer is too small.

## Project Layout

- `src/`: lesson implementation files
- `tests/`: focused regression tests
- `main.c`: entry point that dispatches to the example demos
- `CMakeLists.txt`: build target definitions for each lesson

## Build and Test

From the repository root:

```sh
cmake --preset default
cmake --build --preset default
ctest --preset default --output-on-failure
```

For debug symbols and breakpoints:

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

The detail and rationale for each implementation live at the top of the
corresponding `.c` file, while this README stays at the project level.
