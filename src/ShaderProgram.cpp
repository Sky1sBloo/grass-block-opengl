#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>

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

void ShaderProgram::SetUniformMat4f(const std::string& uniform, const glm::mat4 value)
{
	glUniformMatrix4fv(
			GetUniformLocation(uniform),
			1,
			GL_FALSE,
			glm::value_ptr(value));
}

void ShaderProgram::SetUniformVec3f(const std::string& uniform, const glm::vec3 value)
{
	glUniform3f(GetUniformLocation(uniform), value.x, value.y, value.z);
}

void ShaderProgram::SetUniform1i(const std::string& uniform, int value)
{
	glUniform1i(GetUniformLocation(uniform), value);
}

void ShaderProgram::SetUniform1f(const std::string& uniform, float value)
{
	glUniform1f(GetUniformLocation(uniform), value);
}

