#! /usr/bin/env bash

if [[ "$@" == "run" ]]; then
    ./build/cpp_db
else
    rm -rf build
    cmake -B build &&
        cmake --build build &&
        ./build/cpp_db
fi