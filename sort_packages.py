pkgs = "base-devel clang git make cmake wayland pkgconf ninja doxygen glfw libxkbcommon libx11 libxrandr libxinerama libxcursor libxi gcc-objc glew gtest gdb glibc valgrind debuginfod graphviz"

pkgs_new = pkgs.split()
pkgs_new = sorted(pkgs_new)
print(" ".join(pkgs_new))