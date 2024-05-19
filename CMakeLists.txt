cmake_minimum_required(VERSION 3.28)

project(HWforGAE)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(HWforGAE src/main.cpp
        include/PointStructurePart1.h
        src/PointStructurePart1.cpp
        include/CalculatorPart2.h
        include/MatrixPart3.h
)
