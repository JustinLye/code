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
	int Width, Height;
	unsigned char* Data = nullptr;
	Data = SOIL_load_image(m_Image_fp.c_str(), &Width, &Height, 0, SOIL_LOAD_RGB);
	if (!Data)
	{
		throw std::runtime_error("Failed to load image file " + m_Image_fp);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(Data);
	glBindTexture(GL_TEXTURE_2D, 0);
}