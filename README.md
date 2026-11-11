# Embedded Security Learning

This repository is a long-term, incremental project for learning secure C,
cryptography, firmware security, and hardware security. Implementations are
educational unless explicitly stated otherwise; passing tests does not establish
security for production use.

## Build Requirements

- CMake 3.21 or newer
- A C11 compiler
- Visual Studio Code with the CMake Tools extension

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

On Windows, the `windows-msvc` preset uses the Visual Studio 2022 x64
generator. From PowerShell with the Visual Studio C++ build tools installed,
configure, build, test, and run the executable with:

```powershell
cmake --preset windows-msvc
cmake --build --preset windows-msvc
ctest --preset windows-msvc
.\build\windows-msvc\Debug\embedded_security.exe
```

## Use Visual Studio Code

The commands below are provided by the **CMake Tools** extension
(`ms-vscode.cmake-tools`); they will not appear until the extension is
installed and active. Open this folder in VS Code, install the extension,
and then open the Command Palette with `Ctrl+Shift+P`:

1. **CMake: Select Configure Preset**, then select `default`.
2. **CMake: Configure**.
3. **CMake: Build**.
4. In the CMake Tools sidebar, select `embedded_security` under **Launch**.
5. Run **CMake: Run Without Debugging** to launch the program in the
	integrated terminal.

To run the registered smoke test, run **CMake: Run Tests** from the Command
Palette. The same project can also be built, run, and tested from a terminal
using the commands in the previous section without installing the extension.

## Project Layout

- `src/`: the runnable project entry point
- `CMakeLists.txt`: C11 target, compiler warnings, and CTest registration
- `CMakePresets.json`: repeatable command-line and VS Code configurations

Each later learning step should add one focused implementation and relevant
tests without turning educational cryptography into a production recommendation.
