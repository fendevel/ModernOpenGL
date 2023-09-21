#pragma once

#include <vector>

#include <glad/glad.h>

GLuint create_framebuffer(std::vector<GLuint> const& cols, GLuint depth = GL_NONE);