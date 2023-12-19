#pragma once
#include <glad/glad.h>

#include "VAO.hpp"
#include "BufferObject.hpp"
#include "Primitives.hpp"
/**
 * Class for storing 3d primitive data 
 */
class DrawableObject 
{
public:
	DrawableObject(Primitive& model);
	void Draw();
private:
	// Array and buffer objects
	VAO vao;
	BufferObject vbo;
	BufferObject ebo;
	
	// Storage of vertex data
	Primitive* model;
};
