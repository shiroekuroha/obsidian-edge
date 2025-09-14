# Obsidian-Edge

Obsidian Edge is a student project focused on exploring Graphical Application Programming Interfaces (APIs) using C/C++. The project involves hands-on experience with graphics rendering, shader programming, and user interface design. This initiative allows us to strengthen our programming abilities while gaining valuable insights into effective project organization and teamwork.

This project currently does not have any plans to support Apple's computers.

# Cloning Project:

Git:

```
git clone --recurse-submodules https://github.com/shiroekuroha/Obsidian-Edge.git
```

# Building

## Windows 10/11

### Requires:
- Git: [Download x64](https://github.com/git-for-windows/git/releases/download/v2.51.0.windows.1/Git-2.51.0-64-bit.exe)
- CMake: [Download x64](https://github.com/Kitware/CMake/releases/download/v4.1.0/cmake-4.1.0-windows-x86_64.msi)
- Visual Studio Code: [Download x64](https://code.visualstudio.com/docs/?dv=win64)
- Visual Studio Build Tools: [Download x64](https://aka.ms/vs/17/release/vs_BuildTools.exe)
    - Package Requires:
        - Desktop development with C++
        - (Optional) Linux, Mac and embedded development with C++
- Vulkan SDK(For Vulkan development): [Redirect](https://vulkan.lunarg.com/)

### Optional:
- Doxygen: [Download x64](https://www.doxygen.nl/files/doxygen-1.14.0-setup.exe)

## Linux (Tested on Archlinux)

### Dependencies:
```
base-devel clang cmake debuginfod doxygen gcc-objc gdb git glew glfw glibc graphviz gtest libx11 libxcursor libxi libxinerama libxkbcommon libxrandr make ninja pkgconf valgrind wayland vulkan-icd-loader vulkan-headers
```

# Build Environment

This project works best with VSCode.

### VSCode Extensions:
- CMake Tools: [Redirect](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- Clangd: [Redirect](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd)

#### Optional Extension for debugging with gdb
- C/C++ Debug (gdb): [Redirect](https://open-vsx.org/vscode/item?itemName=KylinIdeTeam.cppdebug)
