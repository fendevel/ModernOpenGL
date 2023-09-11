#include "Util.h"

#include <glm/ext.hpp>

#include <filesystem>
#include <sstream>
#include <fstream>

std::string read_text_file(std::string_view filepath)
{
	if (!std::filesystem::exists(filepath.data()))
	{
		std::ostringstream message;
		message << "file " << filepath.data() << " does not exist.";
		throw std::filesystem::filesystem_error(message.str(), std::make_error_code(std::errc::no_such_file_or_directory));
	}
	std::ifstream file(filepath.data());
	return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

glm::vec3 orbit_axis(float angle, glm::vec3 const& axis, glm::vec3 const& spread) { return glm::angleAxis(angle, axis) * spread; }

float lerp(float a, float b, float f) { return a + f * (b - a); }