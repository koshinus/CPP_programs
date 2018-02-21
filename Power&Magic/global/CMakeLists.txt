cmake_minimum_required(VERSION 3.1)
project(global)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES terrain_features.hpp main.cpp)

add_executable(global ${SOURCE_FILES})
