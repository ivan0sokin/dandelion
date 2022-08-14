add_library(glad STATIC src/glad.c)

target_include_directories(glad PRIVATE include)

target_compile_definitions(glad PRIVATE O3)