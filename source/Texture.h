#pragma once

#include <cstddef>
#include <string_view>
#include <array>

#include <stb_image.h>
#include <glad/glad.h>

using stb_comp_t = int;
GLuint create_texture_2d_from_file(std::string_view filepath, stb_comp_t comp = STBI_rgb_alpha, bool generateMipMaps = false);

GLuint create_texture_2d(GLenum internal_format, GLenum format, GLsizei width, GLsizei height, void* data = nullptr, GLenum filter = GL_LINEAR, GLenum repeat = GL_REPEAT, bool generateMipMaps = false);

GLuint create_texture_cube_from_file(std::array<std::string_view, 6> const& filepath, stb_comp_t comp = STBI_rgb_alpha);

template<typename T = nullptr_t>
GLuint create_texture_cube(GLenum internal_format, GLenum format, GLsizei width, GLsizei height, std::array<T*, 6> const& data)
{
	GLuint tex = 0;
	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &tex);
	glTextureStorage2D(tex, 1, internal_format, width, height);
	for (GLint i = 0; i < 6; ++i)
	{
		if (data[i])
		{
			glTextureSubImage3D(tex, 0, 0, 0, i, width, height, 1, format, GL_UNSIGNED_BYTE, data[i]);
		}
	}
	// Fix cubemap seams
	glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return tex;
}