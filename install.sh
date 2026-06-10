#!/usr/bin/env bash
set -e

echo "=== Installing dependencies ==="

# Install system dependencies for raylib (Linux only)
if command -v apt &>/dev/null; then
    sudo apt update
    sudo apt install -y build-essential git cmake libx11-dev libxrandr-dev libxi-dev libxinerama-dev libxcursor-dev libgl1-mesa-dev libglu1-mesa-dev
elif command -v dnf &>/dev/null; then
    sudo dnf install -y gcc gcc-c++ git cmake libX11-devel libXrandr-devel libXi-devel libXinerama-devel libXcursor-devel mesa-libGL-devel mesa-libGLU-devel
elif command -v pacman &>/dev/null; then
    case "$(uname -s)" in
        MINGW*|MSYS*) echo "  (skipping — Windows/MinGW, libraries provided by toolchain)" ;;
        *) sudo pacman -Sy --noconfirm base-devel git cmake libx11 libxrandr libxi libxinerama libxcursor mesa ;;
    esac
else
    echo "Warning: unsupported package manager. Ensure cmake and a C++ compiler are installed."
fi

# Clean up old raylib artifacts from the previous build approach
rm -rf lib/cmake lib/pkgconfig lib/.raylib_built_linux

echo "=== Done ==="
echo "Run ./run.sh to build and launch."
