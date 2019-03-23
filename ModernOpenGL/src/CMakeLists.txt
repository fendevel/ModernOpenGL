find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(demo source.cpp)

target_link_libraries(demo
    ${SDL2_LIBRARIES}
    glad
    stb
    glm
    dl
    stdc++fs)
