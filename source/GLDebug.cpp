#include "GLDebug.h"

#include <sstream>
#include <iostream>

void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::ostringstream str;
	str << "message: " << message << '\n';
	str << "type: ";
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR: str << "ERROR"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: str << "DEPRECATED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: str << "UNDEFINED_BEHAVIOR";	break;
	case GL_DEBUG_TYPE_PORTABILITY: str << "PORTABILITY"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: str << "PERFORMANCE"; break;
	case GL_DEBUG_TYPE_OTHER: str << "OTHER"; break;
	}

	str << '\n';
	str << "id: " << id << '\n';
	str << "severity: ";
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW: str << "LOW"; break;
	case GL_DEBUG_SEVERITY_MEDIUM: str << "MEDIUM";	break;
	case GL_DEBUG_SEVERITY_HIGH: str << "HIGH";	break;
	default: str << "NONE";
	}

	std::clog << str.str() << std::endl;
}