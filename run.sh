#!/usr/bin/env bash
set -e

case "$OSTYPE" in
    msys*|cygwin*)
        EXE=Game.exe
        LIBS=(-lraylib -lopengl32 -lgdi32 -lwinmm)
        ;;
    *)
        EXE=Game
        LIBS=(-lraylib -lGL -lpthread -ldl -lX11 -lXrandr -lXi)
        ;;
esac

cd build
g++ ../src/*.cpp -o "$EXE" -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ "${LIBS[@]}"
"./$EXE"
cd ..
