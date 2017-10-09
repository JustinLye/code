#ifndef TEXTURE2D_CONN_H_INCLUDED
#define TEXTURE2D_CONN_H_INCLUDED

#include <boost/lexical_cast.hpp>
#include "Component_connector.h"
#include "Texture2D_CMP.h"

class Texture2D_CONN : public Component_connector<Texture_imageCMP, Texture2D_CMP>
{
public:
	Texture2D_CONN();
	virtual ~Texture2D_CONN();
private:
	virtual void connect(const boost::property_tree::ptree& Prop_tree);
};

#endif