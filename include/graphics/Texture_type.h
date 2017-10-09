#ifndef TEXTURE_TYPE_H_INCLUDED
#define TEXTURE_TYPE_H_INCLUDED
#include "Graphics_sys.h"
#include "Component.h"
class Texture_type : public Component
{
public:
	Texture_type() :
		Component(),
		m_Texture_id(~0),
		m_Unit_offset(~0)
	{

	}
	virtual ~Texture_type()
	{

	}
	void set_unit_offset(unsigned int Tex_unit_offset)
	{
		m_Unit_offset = Tex_unit_offset;
	}
	GLuint get_id() const
	{
		return m_Texture_id;
	}
	GLenum get_unit_offset() const
	{
		return m_Unit_offset;
	}
	virtual void generate() = 0;
protected:
	GLuint m_Texture_id;
	GLenum m_Unit_offset;
};

class Texture2D : public Texture_type
{
public:
	Texture2D() :
		Texture_type()
	{

	}
	virtual ~Texture2D()
	{

	}
	virtual void generate();
};

class Texture3D : public Texture_type
{
public:
	Texture3D() :
		Texture_type()
	{

	}
	virtual ~Texture3D()
	{

	}
	virtual void generate();
};

#endif
