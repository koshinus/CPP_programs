cmake_minimum_required(VERSION 3.1)
project(tactical)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES unit.hpp terrain_features.hpp tile.hpp tactical_grid.hpp main.cpp)

add_executable(tactical ${SOURCE_FILES})
