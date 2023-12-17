#include "BufferObject.hpp"

BufferObject::BufferObject(GLenum target) :
	mTarget(target)
{
	glGenBuffers(1, &id);
}

void BufferObject::SetBufferData(GLsizei size, const void* data, GLenum usage)
{
	glBufferData(mTarget, size, data, usage);
}

void BufferObject::Bind()
{
	glBindBuffer(mTarget, id);
}

void BufferObject::Unbind()
{
	glBindBuffer(mTarget, 0);
}
