add_library(stb STATIC
    stb_vorbis.c
)

target_include_directories(stb
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
