#ifndef SHADER_COMP_H_INCLUDED
#define SHADER_COMP_H_INCLUDED

#include "Texture2D_CMP.h"
#include "Shader_progCMP.h"

class Shader_COMP : public Component
{
public:
	Shader_COMP();
	virtual ~Shader_COMP();
protected:
	unsigned int m_Shader_prog_id;
	std::vector<Texture2D_CMP> m_Textures; // this is optional, and may be empty
	friend class Shader_BLDR;
};


#endif