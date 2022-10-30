cmake_minimum_required(VERSION 3.21)
project(Big_Real)

set(CMAKE_CXX_STANDARD 14)

add_executable(Big_Real
        main.cpp bigDecimalIntClass.cpp BigRealClass.cpp)
