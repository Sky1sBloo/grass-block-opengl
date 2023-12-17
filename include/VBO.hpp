#pragma once
#include <glad/glad.h>

class VBO
{
public:
	/**
	 * Default constructor for VBO
	 */
	VBO();
	
	/**
	 * Sets the buffer data
	 *
	 * @param size Size of buffer data
	 * @param data Data for the buffer
	 * @param usage GL_STATIC_DRAW, etc
	 */
	void SetBufferData(const void* data, GLenum usage);
	void Bind();
	void Unbind();

	GLuint GetId() const { return id; }
private:
	GLuint id;
};
