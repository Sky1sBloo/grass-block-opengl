#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>

std::optional<std::string> GetTextFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Error: Cannot open file " << filePath << std::endl;
		return std::nullopt;
	}

	std::ostringstream stringStream;
	stringStream << file.rdbuf();

	file.close();

	std::optional<std::string> fileText = stringStream.str();
	return fileText;
}

Shader::Shader(const std::string& sourcePath, GLenum shaderType)
{
	id = glCreateShader(shaderType);
	std::string sourceStr = GetTextFromFile(sourcePath).value();
	const GLchar* sourceChar = sourceStr.c_str();
	glShaderSource(id, 1, &sourceChar, nullptr);
	glCompileShader(id);

	int success;
	char infolog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infolog);
		std::cerr << "Failed to compile sshader: " << infolog << std::endl;
	}
}

void Shader::DeleteShader()
{
	glDeleteShader(id);
}
