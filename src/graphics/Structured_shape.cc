#include"Structured_shape.h"


Structured_shape::Structured_shape(const GLchar* XML_config_fp) :
	Shape(),
	m_Dimensions(0),
	m_Points(0),
	m_Next_attrib_index(0),
	m_Total_count(0),
	m_Attributes(std::vector<Vertex_attrib>()),
	m_Shader_ptr(nullptr)
{
}

Structured_shape::~Structured_shape()
{

}