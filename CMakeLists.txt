cmake_minimum_required(VERSION 3.19)
project(tensorlite)

set(CMAKE_CXX_STANDARD 20)

include_directories(/Users/gautamsharma/Desktop/C++/googletest/googletest/include/)
include_directories(/Users/gautamsharma/Desktop/C++/googletest/googlemock/include/)

include_directories(include/)

link_directories(/Users/gautamsharma/Desktop/C++/googletest/build/lib/)

add_executable(tensorlite main.cpp src/Tensor.cpp src/Utility.cpp src/Tensor2D.cpp include/Tensor2D.h)

add_executable(test_tensor tests/t_Tensor.cpp src/Tensor.cpp src/Utility.cpp)

add_executable(test_tensor2D src/Tensor.cpp src/Utility.cpp src/Tensor2D.cpp tests/t_Tensor2D.cpp)

target_link_libraries(test_tensor gtest gmock gtest_main)
target_link_libraries(test_tensor2D gtest gmock gtest_main)