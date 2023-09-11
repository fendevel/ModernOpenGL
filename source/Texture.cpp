#include "Texture.h"

#include <filesystem>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLuint create_texture_2d(GLenum internal_format, GLenum format, GLsizei width, GLsizei height, void* data, GLenum filter, GLenum repeat, bool generateMipMaps)
{
	GLuint tex = 0;
	glCreateTextures(GL_TEXTURE_2D, 1, &tex);
	int levels = 1;
	if (generateMipMaps)
	{
		levels = 1 + (int)std::floor(std::log2(std::min(width, height)));
	}
	glTextureStorage2D(tex, levels, internal_format, width, height);


	if (generateMipMaps)
	{
		if (filter == GL_LINEAR)
			glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		else if (filter == GL_NEAREST)
			glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		else
			throw std::runtime_error("Unsupported filter");

	}
	else
	{
		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, filter);
	}
	glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, filter);

	glTextureParameteri(tex, GL_TEXTURE_WRAP_S, repeat);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_T, repeat);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_R, repeat);

	if (data)
	{
		glTextureSubImage2D(tex, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
	}

	if (generateMipMaps) glGenerateTextureMipmap(tex);

	return tex;
}

GLuint create_texture_2d_from_file(std::string_view filepath, stb_comp_t comp, bool generateMipMaps)
{
	int x, y, c;
	if (!std::filesystem::exists(filepath.data()))
	{
		std::ostringstream message;
		message << "file " << filepath.data() << " does not exist.";
		throw std::runtime_error(message.str());
	}
	const auto data = stbi_load(filepath.data(), &x, &y, &c, comp);

	auto const [in, ex] = [comp]() {
		switch (comp)
		{
		case STBI_rgb_alpha:	return std::make_pair(GL_RGBA8, GL_RGBA);
		case STBI_rgb:			return std::make_pair(GL_RGB8, GL_RGB);
		case STBI_grey:			return std::make_pair(GL_R8, GL_RED);
		case STBI_grey_alpha:	return std::make_pair(GL_RG8, GL_RG);
		default: throw std::runtime_error("invalid format");
		}
	}();

	const auto name = create_texture_2d(in, ex, x, y, data, GL_LINEAR, GL_REPEAT, generateMipMaps);
	stbi_image_free(data);
	return name;
}

GLuint create_texture_cube_from_file(std::array<std::string_view, 6> const& filepath, stb_comp_t comp)
{
	int x, y, c;
	std::array<stbi_uc*, 6> faces;

	auto const [in, ex] = [comp]() {
		switch (comp)
		{
		case STBI_rgb_alpha:	return std::make_pair(GL_RGBA8, GL_RGBA);
		case STBI_rgb:			return std::make_pair(GL_RGB8, GL_RGB);
		case STBI_grey:			return std::make_pair(GL_R8, GL_RED);
		case STBI_grey_alpha:	return std::make_pair(GL_RG8, GL_RG);
		default: throw std::runtime_error("invalid format");
		}
	}();

	for (auto i = 0; i < 6; i++)
	{
		faces[i] = stbi_load(filepath[i].data(), &x, &y, &c, comp);
	}

	const auto name = create_texture_cube(in, ex, x, y, faces);

	for (auto face : faces)
	{
		stbi_image_free(face);
	}
	return name;
}