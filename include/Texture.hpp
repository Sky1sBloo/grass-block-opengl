#pragma once
#include <glad/glad.h>
#include <string>
#include <vector>
/**
 * Wrapper class for holding opengl textures
 */
class Texture
{
public:
	/**
	 * Default constructor for Texture
	 *
	 * @param texPath Path to file image
	 * @param internalFormat Number of color components in the texture
	 * @param format Format of pixel data
	 * @param repeat When texCoordinates is above 1
	 */
	Texture(const std::string& texPath, GLenum textureUnit , GLint filter = GL_NEAREST, GLint repeat = GL_REPEAT);


	/**
	 * Wrapper function for glTexParameteri
	 */ 
	void SetParameteri(GLenum paramName, GLint value);

	/**
	 * Generates an image data
	 *
	 * @param path Path to image
	 */
	void LoadImage(const std::string& path);

	/**
	 * Binds and unbinds the texture
	 */
	void Bind();
	void Unbind();

	/**
	 * Returns the id of the texture
	 */
	GLuint GetId() const { return id; }

	/**
	 * Returns the GL_TEXTURE# of the class
	 */
	GLuint GetTextureUnit() const { return mTextureUnit; }
private:
	GLuint id;
	GLenum mTextureUnit;
	int mWidth, mHeight, mNrChannels;
};
