cmake_minimum_required(VERSION 3.10)
project(Wet1StaticEye)

set(CMAKE_CXX_STANDARD 11)

add_executable(Wet1StaticEye exceptions.h testMacros.h tree.h library1.h
        tree.cpp mapElement.h)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors")