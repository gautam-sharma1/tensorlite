cmake_minimum_required(VERSION 3.19)
project(tensorlite)

set(CMAKE_CXX_STANDARD 20)

include_directories(/Users/gautamsharma/Desktop/C++/googletest/googletest/include/)
include_directories(/Users/gautamsharma/Desktop/C++/googletest/googlemock/include/)

include_directories(include/)

link_directories(/Users/gautamsharma/Desktop/C++/googletest/build/lib/)

add_executable(tensorlite main.cpp src/Tensor.cpp include/Utility.h src/Utility.cpp)

add_executable(test tests/t_Tensor.cpp src/Tensor.cpp include/Utility.h src/Utility.cpp)

target_link_libraries(test gtest gmock gtest_main)