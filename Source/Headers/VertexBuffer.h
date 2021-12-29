#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

class VertexBuffer
{
public:
	VertexBuffer(int size, const float* data);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int VBID;
};
#endif // !VERTEX_BUFFER
