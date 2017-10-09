#ifndef __SHAPE_POSITION_ONLY_H_INCLUDED__
#define __SHAPE_POSITION_ONLY_H_INCLUDED__

#include<stdexcept>
#include<fstream>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>

#include"Structured_shape.h"


// This shape has only 3 position data points (x,y,z).
// It is buffered to the GL_ARRAY_BUFFER
class Shape_pos_ab : public Structured_shape
{
public:
	Shape_pos_ab(const GLchar* XML_config_fp = nullptr);
	virtual ~Shape_pos_ab(); // deletes buffers
protected:
	bool m_Gen_buffs_flag; // if true vao & vbo buffers have not been generated.
	GLuint m_VAO;
	GLuint m_VBO;
	
	virtual void configure_shape(const GLchar* XML_config_fp);
	virtual void configure_shape(boost::property_tree::ptree& XML_data);
	virtual void buffer_shape();
	virtual void draw_shape();
	virtual void parse_config_file(const GLchar* XML_config_fp);
	virtual void generate_buffers();
}

#endif