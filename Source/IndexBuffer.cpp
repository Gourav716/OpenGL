#include"Headers/IndexBuffer.h"
#include<glad/glad.h>

IndexBuffer::IndexBuffer(int size, const unsigned int* data)
{
	glad_glGenBuffers(1, &IBID);
	glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
	glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glad_glDeleteBuffers(1, &IBID);
}

void IndexBuffer::Bind() const
{
	glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
}

void IndexBuffer::UnBind() const
{
	glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
