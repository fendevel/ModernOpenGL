#include "Shader.h"

#include <iostream>
#include <array>
#include <sstream>
#include <stdexcept>

#include "Util.h"

void validate_program(GLuint shader)
{
	GLint compiled = 0;
	glProgramParameteri(shader, GL_PROGRAM_SEPARABLE, GL_TRUE);
	glGetProgramiv(shader, GL_LINK_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		std::array<char, 1024> compiler_log;
		glGetProgramInfoLog(shader, compiler_log.size(), nullptr, compiler_log.data());
		glDeleteShader(shader);

		std::ostringstream message;
		message << "shader contains error(s):\n\n" << compiler_log.data() << '\n';
		auto str = message.str();
		throw std::runtime_error(str);
	}
}

std::tuple<GLuint, GLuint, GLuint> create_program_from_files(std::string_view vert_filepath, std::string_view frag_filepath)
{
	auto const vert_source = read_text_file(vert_filepath);
	auto const frag_source = read_text_file(frag_filepath);

	return create_program_from_sources(vert_source, frag_source);
}

std::tuple<GLuint, GLuint, GLuint> create_program_from_sources(std::string_view vert_source, std::string_view frag_source)
{
	auto const v_ptr = vert_source.data();
	auto const f_ptr = frag_source.data();
	GLuint pipeline = 0;

	auto vert = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &v_ptr);
	validate_program(vert);

	auto frag = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &f_ptr);
	validate_program(frag);

	glCreateProgramPipelines(1, &pipeline);
	glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vert);
	glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, frag);

	return std::make_tuple(pipeline, vert, frag);
}

GLuint create_shader(GLuint vert, GLuint frag)
{
	GLuint pipeline = 0;
	glCreateProgramPipelines(1, &pipeline);
	glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vert);
	glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, frag);
	return pipeline;
}

void delete_shader(GLuint pr, GLuint vs, GLuint fs)
{
	glDeleteProgramPipelines(1, &pr);
	glDeleteProgram(vs);
	glDeleteProgram(fs);
}

// Shader code
const char* blurFragSource =
#include "shader/blur.frag.glsl"
;

const char* blurVertSource =
#include "shader/blur.vert.glsl"
;

const char* gbufferFragSource =
#include "shader/gbuffer.frag.glsl"
;

const char* gbufferVertSource =
#include "shader/gbuffer.vert.glsl"
;

const char* mainFragSource =
#include "shader/main.frag.glsl"
;

const char* mainVertSource =
#include "shader/main.vert.glsl"
;