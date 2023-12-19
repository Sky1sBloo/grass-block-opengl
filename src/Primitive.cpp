#include "Primitives.hpp"

Primitive::Primitive(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) :
	mVertices(vertices), mIndices(indices)
{
}
