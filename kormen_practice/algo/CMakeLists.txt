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

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(algo ${SOURCE_FILES})
