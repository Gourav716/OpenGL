#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void LinkAttribute(unsigned int index, int numComponents, int stride, const void* offset);

	void Bind() const;
	void UnBind() const;

private:
	unsigned int VAID;
};
#endif // !VERTEX_ARRAY
