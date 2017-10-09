#include"Shape.h"

Shape::Shape() :
	Component(),
	m_Data_points(std::vector<GLfloat>()),
	m_Rebuffer_flag(true),
	m_Configured_flag(false)
{

}

Shape::~Shape()
{

}

void Shape::configure(const GLchar* XML_config_fp)
{
	configure_shape(XML_config_fp);
	m_Rebuffer_flag = true;
	m_Configured_flag = true;
}

void Shape::buffer()
{
	if (!m_Configured_flag) // Check if the shape is configured
	{
		throw std::runtime_error("Cannot buffer unconfigured Shape object.");
	}
	buffer_shape();
	m_Rebuffer_flag = false;
}

void Shape::draw()
{
	if (m_Rebuffer_flag)
	{
		buffer();
	}
	draw_shape();
}