#pragma once
#include <glad/glad.h>

/**
 * Class definition of Vertex Array Object
 */
class VAO
{
public:
	VAO();

	/**
	 * Wrapper function for glVertexAttribPointer for floating values
	 *
	 * @param idx Location of attribute
	 * @param number of components per generic vertex attribute
	 * @param stride length of each stride (automatically multiplies to size of float)
	 * @param offset offset from start of array (automatically multiplies to size of float)
	 */
	void DefineArrayAttribute(GLuint idx, GLint size, GLuint stride, GLuint offset);

	/**
	 * Binds or unbinds the current VAO
	 */
	void Bind();
	void Unbind();

	GLuint GetId() const { return id; }
private:
	GLuint id;
};
