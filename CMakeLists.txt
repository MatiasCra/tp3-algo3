cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread -std=gnu++17 -ggdb3 -g")
project(tp3_algo3)

set(CMAKE_CXX_STANDARD 17)

add_executable(ej1 ej1/ej1.cpp)
add_executable(ej1benchmark ej1/ej1benchmark.cpp)
add_executable(ej2 ej2/ej2.cpp)
