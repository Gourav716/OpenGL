#include"Headers/Texture.h"
#include<glad/glad.h>
#include<stb_image/stb_image.h>

Texture::Texture(const char* file, int slot)
{
	stbi_set_flip_vertically_on_load(1);

	m_Buffer = stbi_load(file, &m_Width, &m_Height, &m_BPP, 4);

	glad_glGenTextures(1, &TexID);
	glActiveTexture(GL_TEXTURE0 + slot);
	glad_glBindTexture(GL_TEXTURE_2D, TexID);

	glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer);

	glad_glGenerateMipmap(GL_TEXTURE_2D);

	if (m_Buffer)
	{
		stbi_image_free(m_Buffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &TexID);
}

void Texture::Bind() const
{
	glad_glBindTexture(GL_TEXTURE_2D, TexID);
}

void Texture::UnBind() const
{
	glad_glBindTexture(GL_TEXTURE_2D, 0);
}
