#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::vector<Shader*>& shaders)
{
	id = glCreateProgram();

	for (auto shader : shaders)
	{
		glAttachShader(id, shader->GetId());
	}
	glLinkProgram(id);	
}

ShaderProgram::ShaderProgram(std::vector<GLuint> shaders)
{
	id = glCreateProgram();

	for (auto shader : shaders)
	{
		glAttachShader(id, shader);
	}
	glLinkProgram(id);	
}
void ShaderProgram::Use()
{
	glUseProgram(id);
}

GLint ShaderProgram::GetUniformLocation(const std::string& uniform)
{
	return glGetUniformLocation(id, uniform.c_str());
}
