# Cryptography

This topic explores small, educational cryptographic building blocks in a way
that is easy to read and test. Each lesson stays focused on one idea so the
implementation and the reasoning remain easy to follow.

## Lessons

- `xor_cipher`: apply a repeating keystream with XOR to transform a message and
  recover it with the same key.
- `caesar_cipher`: rotate alphabetic characters by a fixed shift while
  preserving letter case and leaving punctuation unchanged.

## Project Layout

- `main.c`: shared demo entry point for the lessons
- `src/`: headers and implementations for each primitive
- `tests/`: focused regression tests for each primitive
- `CMakeLists.txt`: build targets and test registration

## Build and Test

From the repository root:

```sh
cmake --preset default
cmake --build --preset default
ctest --preset default --output-on-failure
```

The detailed reasoning for the implementation lives at the top of the
corresponding `.c` file, while this README remains a project-level overview.
