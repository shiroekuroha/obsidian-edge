#! /bin/bash

cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 --build . --config Debug --target all -- && cd ..
