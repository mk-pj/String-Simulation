cmake_minimum_required(VERSION 3.30)
project(6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_executable(6 src/main.cpp
        src/func.cpp)
