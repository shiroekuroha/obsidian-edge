# Obsidian Edge

Obsidian Edge is a C/C++ graphics programming project focused on exploring modern graphical APIs, rendering systems, shader development, and engine architecture.

The project serves as a learning environment for:

- Graphics API development
- Rendering pipelines
- Shader programming
- UI systems
- C/C++ project organization
- Multi-platform build workflows

---

# Getting Started

## Clone the Repository

Clone the repository with all required submodules:

```bash
git clone --recurse-submodules https://github.com/shiroekuroha/obsidian-edge.git
```

If you already cloned the repository without submodules:

```bash
git submodule update --init --recursive
```

---

# Building

## Supported Platforms

| Platform | Status                               |
| -------- | ------------------------------------ |
| Linux    | Stable on Fedora 41, Archlinux       |
| Windows  | Experimental / Not officially tested |

---

# Windows 10/11

> Windows builds are not officially tested. Build issues may occur.

## Requirements

- Git
  https://gitforwindows.org/

- CMake
  https://cmake.org/download/

- Visual Studio Code
  https://code.visualstudio.com/

- Visual Studio Build Tools
  https://visualstudio.microsoft.com/downloads/

### Required Visual Studio Components

Install:

- Desktop development with C++
- MSVC compiler toolchain
- Windows SDK

Optional:

- Linux and embedded development with C++

## Graphics Development

For Vulkan development:

- Vulkan SDK
  https://vulkan.lunarg.com/

## Optional Tools

- Doxygen (documentation generation)
  https://www.doxygen.nl/

---

# Linux

## Tested Distribution

- Fedora 41
- Arch Linux

## Dependencies

### Fedora

```bash
sudo dnf group install "Development Tools"

sudo dnf install \
clang \
clangd \
cmake \
elfutils-debuginfod-client \
doxygen \
gcc-c++ \
gcc-objc \
gdb \
git \
glew-devel \
glfw-devel \
glibc-devel \
graphviz \
gtest-devel \
libX11-devel \
libXcursor-devel \
libXi-devel \
libXinerama-devel \
libxkbcommon-devel \
libXrandr-devel \
make \
ninja-build \
pkgconf-pkg-config \
valgrind \
wayland-devel \
vulkan-loader-devel \
vulkan-headers \
python
```

### Arch Linux

```bash
sudo pacman -S \
base-devel \
clang \
cmake \
debuuginfod \
doxygen \
gcc-objc \
gdb \
git \
glew \
glfw \
glibc \
graphviz \
gtest \
libx11 \
libxcursor \
libxi \
libxinerama \
libxkbcommon \
libxrandr \
make \
ninja \
pkgconf \
valgrind \
wayland \
vulkan-icd-loader \
vulkan-headers \
python
```

---

# Development Environment

Obsidian Edge is developed primarily with **Visual Studio Code**.

## Recommended Extensions

### CMake Tools

https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools

Provides:

- CMake configuration
- Build management
- Target selection

### Clangd

https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd

Provides:

- C++ language support
- Code completion
- Static analysis

## Optional Debugging Extension

### C/C++ Debug (GDB)

https://open-vsx.org/vscode/item?itemName=KylinIdeTeam.cppdebug

Provides:

- GDB debugging support
- Breakpoints
- Variable inspection

---

# Building the Project

After installing dependencies:

> You can use the provided scripts in ./utility/scripts.

Clean build:

```sh
mkdir build && cd build && cmake .. && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 --build . --config Debug --target all -- && cd ..
```

Rebuild:

```sh
cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 --build . --config Debug --target all -- && cd ..
```

---

# Contributing

Contributions, bug reports, and suggestions are welcome.

When submitting changes:

- Use [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
- Follow the existing C++ style
- Test builds before submitting
- Include relevant build information when reporting issues

---

# License

See the repository license file for details.
