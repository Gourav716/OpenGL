#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS

class Texture
{
public:
	Texture(const char* file, int slot = 0);
	~Texture();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int TexID;
	unsigned char* m_Buffer;
	int m_Width, m_Height, m_BPP;
};
#endif // !TEXTURE_CLASS
