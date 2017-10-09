#include "Texture_type.h"

void Texture2D::generate()
{
	if (m_Unit_offset == ~0)
	{
		throw std::runtime_error("Texture unit must be set");
	}
	
	glGenTextures(1, &m_Texture_id);
	glBindTexture(GL_TEXTURE_2D, m_Texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture3D::generate()
{

}