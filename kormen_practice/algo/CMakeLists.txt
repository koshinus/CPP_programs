cmake_minimum_required(VERSION 3.1)
project(algo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        tests.cpp tests.hpp
        sorts.cpp sorts.hpp
        chapter-7.hpp
        searches.hpp
        chapter-4-1.hpp
        support.hpp
        chapter-12-2.hpp
        abstract_sorter.hpp)

add_executable(algo ${SOURCE_FILES})
