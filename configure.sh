#!/usr/bin/env bash

cmake -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_C_COMPILER=clang -S . -B ./BUILD/
