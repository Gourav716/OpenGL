#include"Headers/VertexBuffer.h"
#include<glad/glad.h>

VertexBuffer::VertexBuffer(int size, const float* data)
{
	glad_glGenBuffers(1, &VBID);
	glad_glBindBuffer(GL_ARRAY_BUFFER, VBID);
	glad_glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glad_glDeleteBuffers(1, &VBID);
}

void VertexBuffer::Bind() const
{
	glad_glBindBuffer(GL_ARRAY_BUFFER, VBID);
}

void VertexBuffer::UnBind() const
{
	glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
}
