#ifndef SHADER_PROGBLDR_H_INCLUDED
#define SHADER_PROGBLDR_H_INCLUDED

#include "Component_builder.h"
#include "Shader_progCMP.h"

class Shader_progBLDR : public Component_builder<Shader_progCMP>
{
public:
	Shader_progBLDR();
	virtual ~Shader_progBLDR();
protected:

	virtual void build(const boost::property_tree::ptree& Prop_tree);
};

#endif