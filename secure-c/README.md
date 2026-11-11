# Secure C: Safe Integer Parsing

## Learning Objective

Convert untrusted decimal text to `int32_t`, rejecting malformed and
out-of-range values. Incorrect parsing can make a validated size, index, or
counter differ from the value later used, leading to memory-safety bugs.

## Accepted Input

The parser accepts an optional leading `+` or `-`, followed by one or more
ASCII decimal digits. It rejects empty strings, whitespace, prefixes,
separators, and trailing characters.

Examples:

```text
"42"         -> success, 42
"-17"        -> success, -17
"+0"         -> success, 0
" 42"        -> invalid format
"42bytes"    -> invalid format
"2147483648" -> out of range for int32_t
```

## Algorithm

1. Reject null input or output pointers.
2. Scan the input grammar. After an optional sign, require at least one ASCII
   digit and reject every other character. This prevents `strtoimax` from
   silently accepting leading whitespace or consuming only a valid prefix.
3. Reset `errno` and convert in base 10 with `strtoimax`, which reports when
   the value cannot be represented by `intmax_t`.
4. Reject `ERANGE` and values outside `INT32_MIN` through `INT32_MAX` before
   narrowing to `int32_t`.
5. Assign the output only after all checks pass. On every error, the caller's
   output remains unchanged.

The parser takes O(n) time and O(1) additional space. Both validation and
conversion scan the string, so excessively long input can still consume time.

## Security Boundaries and Limitations

The function requires a readable, NUL-terminated string. It cannot determine
whether the pointer is valid or whether the underlying buffer is terminated.
Code receiving fixed-size or untrusted buffers must first enforce a maximum
length and safely establish a bounded string. Do not pass an unterminated
buffer to this API.

Parsing a number does not make its later use safe. For example, a parsed size
still needs checks when multiplied, added to another size, used to allocate
memory, or used as an array index. This educational parser is not a complete
input-framing strategy or a claim that downstream operations are secure.

## Tests

`tests/test_safe_integer.c` checks valid signed values and both `int32_t`
boundaries, one-step range failures, malformed and empty inputs, null
arguments, and that failures leave the output unchanged. CTest runs these
cases as `safe_integer_parser`; `safe_integer_demo_smoke` runs the app.

## Step-by-Step Debugging

Run the following commands from the repository root. The `debug` preset
enables debug symbols and writes binaries under `build/debug/`.

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

### VS Code

1. Open the repository root and select the `debug` configure preset with
   **CMake: Select Configure Preset** in the Command Palette.
2. Run **CMake: Configure**, then **CMake: Build**.
3. Open `secure-c/src/safe_integer.c` and set a breakpoint inside
   `parse_int32_decimal`.
4. Select `safe_integer_demo` as the launch target in the CMake Tools view.
5. Run **CMake: Debug**. Use the Debug toolbar to step through the parser,
   inspect variables, continue, or stop.

### GDB

Start the demo under GDB:

```sh
gdb --args ./build/debug/secure-c/safe_integer_demo
```

At the GDB prompt, break in the parser and inspect the input:

```text
(gdb) break parse_int32_decimal
(gdb) run
(gdb) print text
(gdb) next
```

Use `next` to advance through the grammar checks. Execute the `strtoimax`
line before inspecting `parsed`. Use `step` to enter functions with available
source information, `backtrace` to inspect the call stack, `continue` to
resume, and `quit` to exit.

### Valgrind

On Linux, Valgrind Memcheck can detect invalid memory accesses and leaks at
runtime. Install Valgrind using your operating system's package manager, then
run the parser tests:

```sh
valgrind --leak-check=full --show-leak-kinds=all \
    --track-origins=yes \
    ./build/debug/secure-c/test_safe_integer
```

Valgrind complements tests but does not prove memory safety or detect every
bug. It is not available on every platform.

### AddressSanitizer and UndefinedBehaviorSanitizer

GCC and Clang can instrument a separate build with AddressSanitizer and
UndefinedBehaviorSanitizer. These detect many memory errors and undefined
operations during execution:

```sh
cmake -S . -B build/sanitize \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_C_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined"
cmake --build build/sanitize
ctest --test-dir build/sanitize --output-on-failure
```

Sanitizers add runtime overhead and only report issues exercised by the run.
They complement, rather than replace, code review and tests. The commands
above use GCC/Clang-style flags and are not for MSVC.
