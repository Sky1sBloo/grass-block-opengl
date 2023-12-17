#pragma once
#include <glad/glad.h>

class BufferObject 
{
public:
	/**
	 * Default constructor for VBO
	 */
	BufferObject(GLenum target);
	
	/**
	 * Sets the buffer data
	 *
	 * @param size Size of buffer data
	 * @param data Data for the buffer
	 * @param usage GL_STATIC_DRAW, etc
	 */
	void SetBufferData(GLsizei size, const void* data, GLenum usage);
	void Bind();
	void Unbind();

	GLuint GetId() const { return id; }
	GLenum GetTarget() const { return mTarget; }
private:
	GLuint id;
	GLenum mTarget;
};
