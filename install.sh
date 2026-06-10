#!/usr/bin/env bash
set -e

RAYLIB_VERSION=5.5
BUILD_DIR="$(cd "$(dirname "$0")" && pwd)"

echo "=== Installing dependencies & building raylib ==="

# Install system dependencies for raylib
if command -v apt &>/dev/null; then
    sudo apt update
    sudo apt install -y build-essential git cmake libx11-dev libxrandr-dev libxi-dev libxinerama-dev libxcursor-dev libgl1-mesa-dev libglu1-mesa-dev
elif command -v dnf &>/dev/null; then
    sudo dnf install -y gcc gcc-c++ git cmake libX11-devel libXrandr-devel libXi-devel libXinerama-devel libXcursor-devel mesa-libGL-devel mesa-libGLU-devel
elif command -v pacman &>/dev/null; then
    sudo pacman -Sy --noconfirm base-devel git cmake libx11 libxrandr libxi libxinerama libxcursor mesa
else
    echo "Warning: unsupported package manager. Ensure build-essential, cmake, X11/Xrandr/GL dev libs are installed."
fi

# Download and build raylib if not already built for Linux
SENTINEL="$BUILD_DIR/lib/.raylib_built_linux"
if [ ! -f "$SENTINEL" ]; then
    echo "Building raylib for Linux..."
    TEMP_DIR=$(mktemp -d)
    cd "$TEMP_DIR"
    curl -sL "https://github.com/raysan5/raylib/archive/refs/tags/$RAYLIB_VERSION.tar.gz" | tar xz
    cd "raylib-$RAYLIB_VERSION"
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$BUILD_DIR" -DCMAKE_INSTALL_LIBDIR=lib -DBUILD_SHARED_LIBS=OFF
    cmake --build . --parallel
    cmake --install .
    touch "$SENTINEL"
    rm -rf "$TEMP_DIR"
    cd "$BUILD_DIR"
else
    echo "raylib already built for Linux, skipping."
fi

# Ensure build output directory exists
mkdir -p "$BUILD_DIR/build"

echo "=== Done ==="
echo "Run ./run.sh to build and launch."
