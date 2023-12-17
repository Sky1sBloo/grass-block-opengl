#pragma once
#include <fstream>
#include <glad/glad.h>
#include <string>
class Shader
{
public:
	/**
	 * Constructor for Shader
	 *
	 * @param sourcePath Source file for the Shader
	 * @param shaderType GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, ...
	 */
	Shader(const std::string& sourcePath, GLenum shaderType);

	/**
	 * Deletes this shader
	 */
	void DeleteShader();

	/**
	 * Returns the ID of this shader
	 */
	GLuint GetId() const { return id; }
private:
	GLuint id;
};
