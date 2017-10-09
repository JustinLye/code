#ifndef SHADER_PROGCMP_H_INCLUDED
#define SHADER_PROGCMP_H_INCLUDED

#include "Component.h"
#include <string>

class Shader_progCMP : public Component
{
public:
	Shader_progCMP();
	virtual ~Shader_progCMP();
	inline std::string get_vert_fp() const
	{
		return m_Vert_fp;
	}
	inline std::string get_frag_fp() const
	{
		return m_Frag_fp;
	}
protected:
	std::string m_Vert_fp;
	std::string m_Frag_fp;
	friend class Shader_progBLDR;
};

#endif

