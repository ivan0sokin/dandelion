set(CORE dandelion/core/Application.cpp dandelion/core/Window.cpp dandelion/core/Engine.cpp)
set(SOURCES ${CORE})

add_library(dandelion SHARED ${SOURCES})

target_link_libraries(dandelion glfw)
target_include_directories(dandelion PRIVATE ../third_party/glfw-3.3.8/include)

if(WIN32)
    target_compile_definitions(dandelion PRIVATE DANDELION_WINDOWS DANDELION_BUILD)
endif()

option(BUILD_SANDBOX_APP "Build Sandbox application" TRUE)
if(BUILD_SANDBOX_APP)
    add_executable(sandbox sandbox/sandbox.cpp)
    target_include_directories(sandbox PRIVATE dandelion)
    target_link_libraries(sandbox dandelion)
    target_compile_definitions(sandbox PRIVATE DANDELION_WINDOWS)
endif()