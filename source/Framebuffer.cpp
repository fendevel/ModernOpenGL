#include "Framebuffer.h"

#include <array>
#include <stdexcept>

GLuint create_framebuffer(std::vector<GLuint> const& cols, GLuint depth)
{
	GLuint fbo = 0;
	glCreateFramebuffers(1, &fbo);

	for (auto i = 0; i < cols.size(); i++)
	{
		glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0 + i, cols[i], 0);
	}

	std::array<GLenum, 32> draw_buffs;
	for (GLenum i = 0; i < cols.size(); i++)
	{
		draw_buffs[i] = GL_COLOR_ATTACHMENT0 + i;
	}

	glNamedFramebufferDrawBuffers(fbo, cols.size(), draw_buffs.data());

	if (depth != GL_NONE)
	{
		glNamedFramebufferTexture(fbo, GL_DEPTH_ATTACHMENT, depth, 0);
	}

	if (glCheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw std::runtime_error("incomplete framebuffer");
	}
	return fbo;
}
