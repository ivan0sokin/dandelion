set(
    CORE
    dandelion/core/Application.cpp
    dandelion/core/Window.cpp
    dandelion/core/WindowCore.cpp
    dandelion/core/Engine.cpp
    dandelion/core/Logger.cpp
    dandelion/core/Timer.cpp
)

set(
    CONTEXT
    dandelion/context/gl/GLContext.cpp
    dandelion/context/gl/GLShader.cpp
        dandelion/context/gl/GLShaderProgram.cpp
)

set(
    FILESYSTEM
    dandelion/filesystem/FileSystem.cpp
)

set(SOURCES ${CORE} ${CONTEXT} ${FILESYSTEM})

add_library(dandelion SHARED ${SOURCES})

target_link_libraries(dandelion glfw spdlog glad)
target_include_directories(dandelion PRIVATE ../third_party/glfw-3.3.8/include ../third_party/spdlog-1.x/include ../third_party/glad/include)

set(DANDELION_COMPILE_DEFINITIONS GLFW_INCLUDE_NONE)

if(WIN32)
    list(APPEND DANDELION_COMPILE_DEFINITIONS DANDELION_WINDOWS DANDELION_BUILD)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    list(APPEND DANDELION_COMPILE_DEFINITIONS DANDELION_DEBUG)
else()
    list(APPEND DANDELION_COMPILE_DEFINITIONS O3)
endif()

target_compile_definitions(dandelion PRIVATE ${DANDELION_COMPILE_DEFINITIONS})

option(BUILD_SANDBOX_APP "Build Sandbox application" TRUE)
if(BUILD_SANDBOX_APP)
    add_executable(sandbox sandbox/sandbox.cpp)
    target_include_directories(sandbox PRIVATE dandelion)
    target_link_libraries(sandbox dandelion opengl32)
    target_compile_definitions(sandbox PRIVATE DANDELION_WINDOWS)

    if(CMAKE_BUILD_TYPE STREQUAL Release)
        target_compile_definitions(sandbox PRIVATE O3)
    endif()
endif()