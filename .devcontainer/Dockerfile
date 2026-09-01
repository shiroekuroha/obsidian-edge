FROM mcr.microsoft.com/devcontainers/base:ubuntu

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        clangd \
        clang-format \
        clang-tidy \
        cmake \
        doxygen \
        gdb \
        libx11-dev \
        libxinerama-dev \
        libxcursor-dev \
        libxi-dev \
        libxrandr-dev \
        libgl-dev \
        ninja-build \
        pkg-config \
        valgrind \
        libwayland-dev \
        libvulkan1 \
    && rm -rf /var/lib/apt/lists/*
