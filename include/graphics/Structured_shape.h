#ifndef __STRUCTURED_SHAPE_H_INCLUDED__
#define __STRUCTURED_SHAPE_H_INCLUDED__

#include<memory>
#include"Shape.h"
#include"Shader.h"
#include"Constants.h"

struct Vertex_attrib
{
	GLuint Index;
	GLint Size;
	GLenum Type;
	GLboolean Normalized;
	GLsizei Stride;
	const GLvoid* Pointer;
	Vertex_attrib(
		const GLuint& Index_val = 0,
		const GLuint& Size_val = 0,
		const GLenum& Type_val = GL_FLOAT,
		const GLboolean& Normalized_val = GL_FALSE,
		const GLsizei& Stride_val = 0,
		const GLvoid* Pointer_val = nullptr) :
		Index(Index_val),
		Size(Size_val),
		Type(Type_val),
		Normalized(Normalized_val),
		Pointer(Pointer_val)
	{

	}
};


class Structured_shape : public Shape
{
public:
	Structured_shape(const GLchar* XML_config_fp = nullptr);
	virtual ~Structured_shape();
	virtual inline void use_program(const std::shared_ptr<const Shader>& Shader_ptr)
	{
		m_Shader_ptr = Shader_ptr;
	}
protected:
	GLuint m_Dimensions; // Total dimensions of shape data (i.e. position (+3), color (+3), texture (+2))
	GLuint m_Points; // Total number of data points
	GLuint m_Next_attrib_index; // Keeps track of attribute indices
	GLuint m_Total_count; // Keeps track of total attribute size, used to set offset value
	std::vector<Vertex_attrib> m_Attributes; // Vector of attributes
	std::shared_ptr<const Shader> m_Shader_ptr;

	virtual void parse_config_file(const GLchar* XML_config_fp) = 0; // Parses configuration file and sets related data members
};

#endif
