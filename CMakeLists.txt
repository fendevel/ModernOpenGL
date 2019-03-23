cmake_minimum_required(VERSION 3.12)

project(demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_subdirectory(ModernOpenGL/deps/glad)
add_subdirectory(ModernOpenGL/deps/stb-master)
add_subdirectory(ModernOpenGL/deps/glm)
add_subdirectory(ModernOpenGL/src)
