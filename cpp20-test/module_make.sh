#!/bin/bash

#clang++-8 -std=c++2a -fmodules-ts --precompile module.cppm -o module.pcm
#clang++-8 -std=c++2a -fmodules-ts -c module.pcm -o module.o
#clang++-8 -std=c++2a -fmodules-ts -fprebuilt-module-path=. module.o module_main.cpp -o module_test


clang++-8 -std=c++2a -fmodules-ts --precompile math.cppm -o math.pcm
clang++-8 -std=c++2a -fmodules-ts -c math.pcm -o math.o
clang++-8 -std=c++2a -fmodules-ts -fprebuilt-module-path=. math.o main.cpp -o math
