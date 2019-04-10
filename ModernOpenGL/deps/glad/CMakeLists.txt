add_library(glad STATIC
    src/glad.c
)

target_include_directories(glad
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
