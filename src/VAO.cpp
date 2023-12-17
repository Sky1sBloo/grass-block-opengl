#include "VAO.hpp"

VAO::VAO()
{
	glGenVertexArrays(1, &id);
}

void VAO::DefineArrayAttribute(GLuint idx, GLint size, GLuint stride, GLuint offset)
{
	glVertexAttribPointer(idx, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(idx);
}

void VAO::Bind()
{
	glBindVertexArray(id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}
