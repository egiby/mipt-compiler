#!/usr/bin/env bash

mkdir -p tmp
cd tmp
# rm -rf *
cmake .. -DCMAKE_BUILD_TYPE=Release

make
