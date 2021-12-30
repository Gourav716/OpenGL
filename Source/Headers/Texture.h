#ifndef TEXTURE_CLASS
#define TEXTURE_CLASS

class Texture
{
public:
	Texture(const char* file, unsigned int format, unsigned int slot = 0);
	~Texture();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int TexID;
	unsigned char* m_Buffer;
	int m_Width, m_Height, m_BPP;
	unsigned int m_Slot;
};
#endif // !TEXTURE_CLASS
