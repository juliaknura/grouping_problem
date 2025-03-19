#!/bin/bash

cd build
cmake --build . --target flatc
cd ..
./build/_deps/flatbuffers-build/flatc --cpp -o ./build/generated ./schemas/problem.fbs
cd build
cmake --build . --target groupingProblem