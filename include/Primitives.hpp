#pragma once
#include <glad/glad.h>
#include <vector>

/**
 * Base class of primitive class
 */
class Primitive 
{
public:
	Primitive() {}
	Primitive(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
	const std::vector<GLfloat>& GetVertices() const { return mVertices; }
	const std::vector<GLuint>& GetIndices() const { return mIndices; }
protected:
	std::vector<GLfloat> mVertices;
	std::vector<GLuint> mIndices;
};

/**
 * Textured Cube with UV map coordinates
 * 0 1 2 3 4
 *0  ---
 *   |t|
 *1--|-|----
 * |l|f|r|b|
 *2--|-|----
 *   |b|
 *3  ---
 */
class Cube : public Primitive
{
public:
	Cube();
private:
	const float cubeUVCol[5] = { 0, 0.25f, 0.5f, 0.75f, 1.f };
	const float cubeUVRow[4] = { 0, 1.f / 3.f, 2.f / 3.f, 1.f };

};

