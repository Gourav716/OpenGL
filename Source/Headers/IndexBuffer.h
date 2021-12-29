#ifndef INDEX_BUFFER
#define INDEX_BUFFER

class IndexBuffer
{
public:
	IndexBuffer(int size, const unsigned int* data);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int IBID;
};
#endif // !INDEX_BUFFER
