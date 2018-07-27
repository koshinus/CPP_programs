cmake_minimum_required(VERSION 3.5)
project(client)

set( CMAKE_CXX_STANDARD 14 )

set( Boost_USE_STATIC_LIBS off )
set( Boost_USE_MULTITHREAD on )
find_package(Boost 1.55.0 REQUIRED COMPONENTS system thread regex)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set( ASIO_REQ_LIBS  ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})
set( SOURCE_FILES ${ASIO_REQ_LIBS} ../common/utilities.hpp ../common/utilities.cpp client.cpp)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fopenmp")

add_executable(client ${SOURCE_FILES})
target_link_libraries(client boost_system gomp pthread)
