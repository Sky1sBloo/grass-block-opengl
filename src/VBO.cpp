#include "VBO.hpp"

VBO::VBO()
{
	glGenBuffers(1, &id);
}

void VBO::SetBufferData(const void* data, GLenum usage)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, usage);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
