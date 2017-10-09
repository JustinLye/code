#ifndef __Parse_shape_H_INCLUDED__
#define __Parse_shape_H_INCLUDED__
#include"Graphics_sys.h" //for opengl headers
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
#include<fstream>
#include<vector>
#include<mutex>

struct Shape_data_pack
{
	GLuint Total_data_points;
	GLuint Total_dimensions;
	std::vector<GLfloat> Data_points;
	std::vector<GLfloat> Element_buffer;
	bool Has_position_data;
	bool Has_color_data;
	bool Has_texture_data;
	Shape_data_pack();
};

class Parse_shape
{
public:
	static Parse_shape* instance();
	Shape_data_pack parse_shape_data(const GLchar* XML_file_path);
private:
	Parse_shape() {}
	Parse_shape(const Parse_shape&) {}
	Parse_shape(Parse_shape&&) {}
	~Parse_shape() {}
	static Parse_shape* Instance_ptr;
	std::mutex Parsing_mtx;
};
#endif
