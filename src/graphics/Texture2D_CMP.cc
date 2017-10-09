#include "Texture2D_CMP.h"

Texture2D_CMP::Texture2D_CMP() :
	Texture2D(),
	m_Image_fp("")
{

}

Texture2D_CMP::~Texture2D_CMP()
{

}

void Texture2D_CMP::load()
{
	if (m_Image_fp == "")
	{
		throw std::runtime_error("Image file path cannot be blank.");
	}
	generate();
	int Width, Height, nrChannels;
	unsigned char* Data = nullptr;
	Data = stbi_load(m_Image_fp.c_str(), &Width, &Height, &nrChannels, 0);
	if (!Data)
	{
		throw std::runtime_error("Failed to load image file " + m_Image_fp);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
	stbi_image_free(Data);
}