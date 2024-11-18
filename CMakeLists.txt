cmake_minimum_required(VERSION 3.29)
project(ArgParserForAristarkh)

set(CMAKE_CXX_STANDARD 20)

add_executable(ArgParserForAristarkh main.cpp
        argparser.cpp
        argparser.h
)
