#!/usr/bin/env bash

mkdir -p tmp
cd tmp
cmake .. -DCMAKE_BUILD_TYPE=Release

make
