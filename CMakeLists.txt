cmake_minimum_required(VERSION 3.8)
project(MathTestPlus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ZklComputer.cpp ZklComputer.h)
add_executable(MathTestPlus ${SOURCE_FILES})