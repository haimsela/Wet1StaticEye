cmake_minimum_required(VERSION 3.10)
project(Wet1StaticEye)

set(CMAKE_CXX_STANDARD 11)

add_executable(Wet1StaticEye library2.h library2.cpp list.h mapElement.h MapTree.h MapList.h tree.h Image.cpp Image.h StaticEye.cpp StaticEye.h main.cpp tests.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors")