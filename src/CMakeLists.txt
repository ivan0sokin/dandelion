set(CORE core/Window.cpp core/Application.cpp)
set(SOURCES ${CORE})

add_library(dandelion SHARED ${SOURCES})

if(WIN32)
    target_compile_definitions(dandelion PRIVATE DANDELION_WINDOWS DANDELION_BUILD)
endif()