#include "EBO.hpp"

EBO::EBO()
{
	glGenBuffers(1, &id);
}

void EBO::SetBufferData(const void* data, GLenum usage)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, usage);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
