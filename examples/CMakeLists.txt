cmake_minimum_required(VERSION 3.17)
project(examples)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES
        "../src/Tensor.cpp"
        "../src/Utility.cpp"
        )

include_directories(../include/)


message("Build Starting!")



add_executable(example_1 example_1.cpp ${SOURCES})
