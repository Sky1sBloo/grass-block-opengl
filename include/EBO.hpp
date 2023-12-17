#pragma once
#include <glad/glad.h>

class EBO
{
public:
	EBO();

	void SetBufferData(const void* data, GLenum usage);
	void Bind();
	void Unbind();

	GLuint GetId() const { return id; }
private:
	GLuint id;
};
