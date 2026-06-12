#!/usr/bin/env bash
set -e

echo "=== Installing dependencies ==="

case "$(uname -s)" in
    MINGW*|MSYS*|CYGWIN*)
        echo "  Windows/MinGW detected — libraries are provided by the toolchain."
        echo "  No additional system packages needed."
        ;;
    Linux*)
        if command -v apt &>/dev/null; then
            sudo apt update
            sudo apt install -y build-essential git cmake libx11-dev libxrandr-dev libxi-dev libxinerama-dev libxcursor-dev libgl1-mesa-dev libglu1-mesa-dev
        elif command -v dnf &>/dev/null; then
            sudo dnf install -y gcc gcc-c++ git cmake libX11-devel libXrandr-devel libXi-devel libXinerama-devel libXcursor-devel mesa-libGL-devel mesa-libGLU-devel
        elif command -v pacman &>/dev/null; then
            sudo pacman -Sy --noconfirm base-devel git cmake libx11 libxrandr libxi libxinerama libxcursor mesa
        else
            echo "Warning: unsupported package manager. Ensure cmake and a C++ compiler are installed."
        fi
        ;;
    Darwin*)
        echo "  macOS detected."
        if command -v brew &>/dev/null; then
            echo "  Installing raylib via Homebrew..."
            brew install raylib cmake
        else
            echo "  Install Homebrew from https://brew.sh, then run:"
            echo "    brew install raylib cmake"
        fi
        ;;
    *)
        echo "Warning: unsupported platform. Ensure cmake and a C++ compiler are installed."
        ;;
esac

# Clean up old raylib artifacts from the previous build approach
rm -rf lib/cmake lib/pkgconfig lib/.raylib_built_linux

echo "=== Done ==="
echo "Run ./run.sh to build and launch."
