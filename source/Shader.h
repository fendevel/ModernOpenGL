#pragma once

#include <string_view>
#include <tuple>
#include <stdexcept>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void validate_program(GLuint shader);

std::tuple<GLuint, GLuint, GLuint> create_program_from_files(std::string_view vert_filepath, std::string_view frag_filepath);

std::tuple<GLuint, GLuint, GLuint> create_program_from_sources(std::string_view vert_source, std::string_view frag_source);

GLuint create_shader(GLuint vert, GLuint frag);

void delete_shader(GLuint pr, GLuint vs, GLuint fs);

template <typename T>
void set_uniform(GLuint shader, GLint location, T const& value)
{
	if constexpr (std::is_same_v<T, GLint>) glProgramUniform1i(shader, location, value);
	else if constexpr (std::is_same_v<T, GLuint>) glProgramUniform1ui(shader, location, value);
	else if constexpr (std::is_same_v<T, bool>) glProgramUniform1ui(shader, location, value);
	else if constexpr (std::is_same_v<T, GLfloat>) glProgramUniform1f(shader, location, value);
	else if constexpr (std::is_same_v<T, GLdouble>) glProgramUniform1d(shader, location, value);
	else if constexpr (std::is_same_v<T, glm::vec2>) glProgramUniform2fv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::vec3>) glProgramUniform3fv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::vec4>) glProgramUniform4fv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::ivec2>) glProgramUniform2iv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::ivec3>) glProgramUniform3iv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::ivec4>) glProgramUniform4iv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::uvec2>) glProgramUniform2uiv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::uvec3>) glProgramUniform3uiv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::uvec4>) glProgramUniform4uiv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::quat>) glProgramUniform4fv(shader, location, 1, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::mat3>) glProgramUniformMatrix3fv(shader, location, 1, GL_FALSE, glm::value_ptr(value));
	else if constexpr (std::is_same_v<T, glm::mat4>) glProgramUniformMatrix4fv(shader, location, 1, GL_FALSE, glm::value_ptr(value));
	else throw std::runtime_error("unsupported type");
}

// Shader source code
extern const char* blurFragSource;
extern const char* blurVertSource;
extern const char* gbufferFragSource;
extern const char* gbufferVertSource;
extern const char* mainFragSource;
extern const char* mainVertSource;