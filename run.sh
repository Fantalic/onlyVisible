#!/usr/bin/env bash
set -e

BUILD_DIR="build"

configure() {
    case "$OSTYPE" in
        msys*|cygwin*) cmake -B "$BUILD_DIR" -S . -G "MinGW Makefiles" ;;
        *)             cmake -B "$BUILD_DIR" -S . ;;
    esac
}

configure 2>/dev/null || { rm -rf "$BUILD_DIR" && configure; }

cmake --build "$BUILD_DIR"

case "$OSTYPE" in
    msys*|cygwin*) "./$BUILD_DIR/Game.exe" ;;
    *)             "./$BUILD_DIR/Game" ;;
esac
