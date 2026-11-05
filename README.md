# Embedded Security Learning

This repository is a long-term, incremental project for learning secure C,
cryptography, firmware security, and hardware security. Implementations are
educational unless explicitly stated otherwise; passing tests does not establish
security for production use.

## Build Requirements

- CMake 3.21 or newer
- A C11 compiler
- For Visual Studio, Visual Studio 2022 with the C++ development workload and
	CMake support

## Build and Test from the Command Line

The `default` preset uses CMake's default generator for the current platform.
From the repository root, configure, build, and run the smoke test with:

```sh
cmake --preset default
cmake --build --preset default
ctest --preset default
```

The executable is written under `build/default/`. CMake chooses the platform's
normal executable name, such as `embedded_security` or
`embedded_security.exe`.

## Use Visual Studio

Open this folder in Visual Studio 2022 using **File > Open > Folder**. Select
the `windows-msvc` configure preset, then build and run the
`embedded_security` startup target. The same preset can be used from a
Developer PowerShell or Developer Command Prompt:

```powershell
cmake --preset windows-msvc
cmake --build --preset windows-msvc
ctest --preset windows-msvc
```

## Project Layout

- `src/`: the runnable project entry point
- `CMakeLists.txt`: C11 target, compiler warnings, and CTest registration
- `CMakePresets.json`: repeatable command-line and Visual Studio configurations

Each later learning step should add one focused implementation and relevant
tests without turning educational cryptography into a production recommendation.