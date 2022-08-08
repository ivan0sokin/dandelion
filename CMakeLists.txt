cmake_minimum_required(VERSION 3.16)
project(dandelion)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)

add_executable(sandbox sandbox/sandbox.cpp)
target_include_directories(sandbox PRIVATE src)
target_link_libraries(sandbox dandelion)
target_compile_definitions(sandbox PRIVATE DANDELION_WINDOWS)