#pragma once

#include <string>
#include <chrono>
#include <cstdio>
#include <string_view>
#include <memory>

#include <glm/glm.hpp>

std::string read_text_file(std::string_view filepath);

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	const size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template<typename T = std::chrono::milliseconds>
int64_t now()
{
	return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

glm::vec3 orbit_axis(float angle, glm::vec3 const& axis, glm::vec3 const& spread);

float lerp(float a, float b, float f);
