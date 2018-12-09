cmake_minimum_required(VERSION 3.10)
project(Wet1StaticEye)

set(CMAKE_CXX_STANDARD 11)

add_executable(Wet1StaticEye library2.h list.h main2.cpp mapElement.h MapTree.h MapList.h tree.h Image.cpp Image.h StaticEye.cpp StaticEye.h)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors")