#include"Headers/VertexArray.h"
#include<glad/glad.h>

VertexArray::VertexArray()
{
	glad_glGenVertexArrays(1, &VAID);
	glad_glBindVertexArray(VAID);
}

VertexArray::~VertexArray()
{
	glad_glDeleteVertexArrays(1, &VAID);
}

void VertexArray::LinkAttribute(unsigned int index, int numComponents, int stride, const void* offset)
{
	glad_glVertexAttribPointer(index, numComponents, GL_FLOAT, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(index);
}

void VertexArray::Bind() const
{
	glad_glBindVertexArray(VAID);
}

void VertexArray::UnBind() const
{
	glad_glBindVertexArray(0);
}
