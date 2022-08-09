cmake_minimum_required(VERSION 3.16)
project(dandelion)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src ${CMAKE_CURRENT_BINARY_DIR}/out)
add_subdirectory(third_party ${CMAKE_CURRENT_BINARY_DIR}/third_party)