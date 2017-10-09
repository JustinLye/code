#ifndef TEXTURE2D_CMP_H_INCLUDED
#define TEXTURE2D_CMP_H_INCLUDED
#include "Texture_type.h"
#include "Texture_imageCMP.h"
#include "SOIL.h"

class Texture2D_CMP : public Texture2D
{
public:
	Texture2D_CMP();
	virtual ~Texture2D_CMP();
	void set_image_fp(const std::string& Image_fp)
	{
		m_Image_fp = Image_fp;
	}
	virtual void load();
protected:
	std::string m_Image_fp;
	friend class Texture2D_CONN;

};

#endif