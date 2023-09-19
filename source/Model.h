#pragma once

#include <tuple>
#include <vector>
#include <stdexcept>

#include <glad/glad.h>
#include <glm/glm.hpp>

struct vertex_t
{
	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 color = glm::vec3(0.f);
	glm::vec3 normal = glm::vec3(0.f);
	glm::vec2 texcoord = glm::vec2(0.f);

	vertex_t(glm::vec3 const& position, glm::vec3 const& color, glm::vec3 const& normal, glm::vec2 const& texcoord)
		: position(position), color(color), normal(normal), texcoord(texcoord) {}
};

struct attrib_format_t
{
	GLuint attrib_index = 0;
	GLint size = 0;
	GLenum type = 0;
	GLuint relative_offset = 0;
};

template<typename T>
constexpr std::pair<GLint, GLenum> type_to_size_enum()
{
	if constexpr (std::is_same_v<T, float>)
		return std::make_pair(1, GL_FLOAT);
	if constexpr (std::is_same_v<T, int>)
		return std::make_pair(1, GL_INT);
	if constexpr (std::is_same_v<T, unsigned int>)
		return std::make_pair(1, GL_UNSIGNED_INT);
	if constexpr (std::is_same_v<T, glm::vec2>)
		return std::make_pair(2, GL_FLOAT);
	if constexpr (std::is_same_v<T, glm::vec3>)
		return std::make_pair(3, GL_FLOAT);
	if constexpr (std::is_same_v<T, glm::vec4>)
		return std::make_pair(4, GL_FLOAT);
	throw std::runtime_error("unsupported type");
}

template<typename T>
inline attrib_format_t create_attrib_format(GLuint attrib_index, GLuint relative_offset)
{
	auto const [comp_count, type] = type_to_size_enum<T>();
	return attrib_format_t{ attrib_index, comp_count, type, relative_offset };
}

template<typename T>
inline GLuint create_buffer(std::vector<T> const& buff, GLenum flags = GL_DYNAMIC_STORAGE_BIT)
{
	GLuint name = 0;
	glCreateBuffers(1, &name);
	glNamedBufferStorage(name, sizeof(typename std::vector<T>::value_type) * buff.size(), buff.data(), flags);
	return name;
}

template<typename T>
std::tuple<GLuint, GLuint, GLuint> create_geometry(std::vector<T> const& vertices, std::vector<uint8_t> const& indices, std::vector<attrib_format_t> const& attrib_formats)
{
	GLuint vao = 0;
	auto vbo = create_buffer(vertices);
	auto ibo = create_buffer(indices);

	glCreateVertexArrays(1, &vao);
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(T));
	glVertexArrayElementBuffer(vao, ibo);

	for (auto const& format : attrib_formats)
	{
		glEnableVertexArrayAttrib(vao, format.attrib_index);
		glVertexArrayAttribFormat(vao, format.attrib_index, format.size, format.type, GL_FALSE, format.relative_offset);
		glVertexArrayAttribBinding(vao, format.attrib_index, 0);
	}

	return std::make_tuple(vao, vbo, ibo);
}

std::vector<glm::vec3> calc_tangents(std::vector<vertex_t> const& vertices, std::vector<uint8_t> const& indices);