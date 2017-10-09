#ifndef __TEXTURE_IMAGEBLDR_H_INCLUDED__
#define __TEXTURE_IMAGEBLDR_H_INCLUDED__
#include"Component_builder.h"
#include"Texture_imageCMP.h"


class Texture_imageBLDR : public Component_builder<Texture_imageCMP>
{
public:
	
	Texture_imageBLDR();
	virtual ~Texture_imageBLDR();

protected:
	virtual void build(const boost::property_tree::ptree& Prop_tree);

};

#endif
