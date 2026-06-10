#!/usr/bin/env bash
set -e
cd build
g++ ../src/*.cpp -o Game -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lGL -lpthread -ldl -lX11 -lXrandr -lXi
./Game
cd ..
