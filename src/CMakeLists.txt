set(CORE dandelion/core/Application.cpp dandelion/core/Window.cpp dandelion/core/WindowCore.cpp dandelion/core/Engine.cpp dandelion/core/Logger.cpp)
set(SOURCES ${CORE})

add_library(dandelion SHARED ${SOURCES})

target_link_libraries(dandelion glfw spdlog)
target_include_directories(dandelion PRIVATE ../third_party/glfw-3.3.8/include ../third_party/spdlog-1.x/include)

set(DANDELION_COMPILE_DEFINITIONS GLFW_INCLUDE_NONE)

if(WIN32)
    list(APPEND DANDELION_COMPILE_DEFINITIONS DANDELION_WINDOWS DANDELION_BUILD)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    list(APPEND DANDELION_COMPILE_DEFINITIONS DANDELION_DEBUG)
endif()

target_compile_definitions(dandelion PRIVATE ${DANDELION_COMPILE_DEFINITIONS})

option(BUILD_SANDBOX_APP "Build Sandbox application" TRUE)
if(BUILD_SANDBOX_APP)
    add_executable(sandbox sandbox/sandbox.cpp)
    target_include_directories(sandbox PRIVATE dandelion)
    target_link_libraries(sandbox dandelion opengl32)
    target_compile_definitions(sandbox PRIVATE DANDELION_WINDOWS)
endif()