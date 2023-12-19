#include "DrawableObject.hpp"
#include "Primitives.hpp"
#include <iostream>

DrawableObject::DrawableObject(Primitive& primitive) :
	vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER), model(&primitive)
{
	vao.Bind();

	vbo.Bind();

	vbo.SetBufferData(primitive.GetVertices().size() * sizeof(primitive.GetVertices()),
			&primitive.GetVertices().front(),
		       	GL_STATIC_DRAW);


	ebo.Bind();
	ebo.SetBufferData(primitive.GetIndices().size() * sizeof(primitive.GetIndices()),
			&primitive.GetIndices().front(),
		       	GL_STATIC_DRAW);

	vao.DefineArrayAttribute(0, 3, 5, 0);
	vao.DefineArrayAttribute(1, 2, 5, 3);

	vbo.Unbind();
	vao.Unbind();
	ebo.Unbind();
}

void DrawableObject::Draw()
{
	vao.Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}
