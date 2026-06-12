#!/usr/bin/env bash
set -e

BUILD_DIR="build"

detect_platform() {
    case "$OSTYPE" in
        msys*|cygwin*)  echo "windows" ;;
        linux-gnu*)
            if grep -qi microsoft /proc/version 2>/dev/null; then
                echo "wsl"
            else
                echo "linux"
            fi
            ;;
        darwin*)        echo "macos" ;;
        *)              echo "unix" ;;
    esac
}

configure() {
    case "$(detect_platform)" in
        windows) cmake -B "$BUILD_DIR" -S . -G "MinGW Makefiles" ;;
        *)       cmake -B "$BUILD_DIR" -S . ;;
    esac
}

configure 2>/dev/null || { rm -rf "$BUILD_DIR" && configure; }

cmake --build "$BUILD_DIR"

case "$(detect_platform)" in
    windows) "./$BUILD_DIR/Game.exe" ;;
    *)       "./$BUILD_DIR/Game" ;;
esac
