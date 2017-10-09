#ifndef __TEXTURE_IMAGE_CMP_H_INCLUDED___
#define __TEXTURE_IMAGE_CMP_H_INCLUDED___

#include "Component.h"
#include<string>

class Texture_imageCMP : public Component
{
public:
	Texture_imageCMP();
	virtual ~Texture_imageCMP();
	inline std::string get_image_fp() const
	{
		return m_Image_fp;
	}
protected:
	std::string m_Image_fp;
	friend class Texture_imageBLDR;
};

#endif