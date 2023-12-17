#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

#include "Shader.hpp"

/**
 * Class for a shader program
 */
class ShaderProgram
{
public:
	/**
	 * Default constructor for shader program
	 *
	 * @param vec Vector of shaders
	 */
	ShaderProgram(const std::vector<Shader*>& shaders);

	ShaderProgram(std::vector<GLuint> shaders);

	/**
	 * Gets the uniform location of variable
	 *
	 * @param uniform Name of the uniform
	 *
	 * @return Location of uniform
	 */
	GLint GetUniformLocation(const std::string& uniform);

	/**
	 * Sets the program as active program
	 */
	void Use();	

	/**
	 * Gets the ID of the program
	 *
	 * @return ID of the program
	 */
	GLuint GetId() const { return id; }
private:
	GLuint id;
};
