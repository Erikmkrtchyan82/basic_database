#! /usr/bin/env bash

rm -rf build
cmake -B build &&
    cmake --build build &&
    ./build/cpp_db
