#ifndef __SHAPE_H_INCLUDED__
#define __SHAPE_H_INCLUDED__

#include<vector>
#include"Graphics_sys.h" //for opengl headers
#include"Parse_shape.h"

class Shape
{
public:
	Shape();
	Shape(const GLuint& Data_points, const GLuint& Data_dims, const GLfloat* Data);
	Shape(const GLuint& Data_points, const GLuint& Data_dims, const std::vector<GLfloat>& Data);
	Shape(const GLchar* XML_file_path);
	virtual ~Shape();
	// Observers
	inline virtual GLuint get_points() const
	{
		return Points;
	}
	inline virtual GLuint get_dimensions() const
	{
		return Dimensions;
	}

	// Modifiers
	virtual void set_data(const GLuint& Data_points, const GLuint& Data_dims, const GLfloat* Data);

	// Functions
	virtual void draw() = 0;
protected:
	GLuint Points;
	GLuint Dimensions;
	GLfloat* Point_data;
	Shape_data_pack Data_pack;
};

#endif