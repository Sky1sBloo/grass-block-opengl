#include "Texture.hpp"
#include <iostream>
#include <stb_image.h>

Texture::Texture(const std::string& texPath, GLenum textureUnit ,GLint filter, GLint repeat) :
	mTextureUnit(textureUnit)
{
	glGenTextures(1, &id);
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, id);

	SetParameteri(GL_TEXTURE_WRAP_S, repeat);
	SetParameteri(GL_TEXTURE_WRAP_T, repeat);
	SetParameteri(GL_TEXTURE_MIN_FILTER, filter);
	SetParameteri(GL_TEXTURE_MAG_FILTER, filter);

	LoadImage(texPath);

	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::SetParameteri(GLenum paramName, GLint value)
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, paramName, value);
}


void Texture::LoadImage(const std::string& path)
{
	unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &mNrChannels, 0);

	if (data)
	{
		GLenum format = (mNrChannels == 3) ? GL_RGB : GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture: " << stbi_failure_reason() << std::endl;
	}

	stbi_image_free(data);
}

void Texture::Bind()
{
	glActiveTexture(mTextureUnit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
