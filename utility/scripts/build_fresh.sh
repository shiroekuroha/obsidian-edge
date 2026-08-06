#! /bin/bash

rm -r build
mkdir build && cd build && cmake .. && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 --build . --config Debug --target all -- && cd ..
