cmake_minimum_required(VERSION 3.23)
project(LinesLib)

set(CMAKE_CXX_STANDARD 14)

add_executable(myStrLib main.cpp linesLib.cpp UnitTests.cpp ProgramHelper.cpp)
