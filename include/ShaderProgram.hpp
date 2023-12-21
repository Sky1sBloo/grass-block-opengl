#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

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
	 * Sets the program as active program
	 */
	void Use();	

	/**
	 * Gets the ID of the program
	 *
	 * @return ID of the program
	 */
	GLuint GetId() const { return id; }
	
	/**
	 * Gets the uniform location of variable
	 *
	 * @param uniform Name of the uniform
	 *
	 * @return Location of uniform
	 */
	GLint GetUniformLocation(const std::string& uniform);

	/**
	 * Sets the uniform of the shader
	 *
	 * @param uniform Name of the uniform
	 * @param value New value of the uniform 
	 */
	void SetUniformMat4f(const std::string& uniform, const glm::mat4 value);
	void SetUniformVec3f(const std::string& uniform, const glm::vec3 value);
	void SetUniform1i(const std::string& uniform, int value);
	void SetUniform1f(const std::string& uniform, float value);
private:
	GLuint id;
};
