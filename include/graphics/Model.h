#ifndef __MODEL_H_INCLUDED__
#define __MODEL_H_INCLUDED__

#include<vector>
#define GLEW_STATIC
#include<GL/glew.h>
#include"Shape.h"

struct Attribute
{
	GLuint Index, Count, Stride, Offset;
	Attribute(
		const GLuint& Attrib_index = 0,
		const GLuint& Attrib_count = 0,
		const GLuint& Attrib_stride = 0,
		const GLuint& Attrib_offset = 0) :
		Index(Attrib_index),
		Count(Attrib_count),
		Stride(Attrib_stride),
		Offset(Attrib_offset)
	{

	}
};

class Model : public Shape
{
public:
	Model();
	Model(const GLuint& Data_points, const GLuint& Data_dims, const GLfloat* Data);
	Model(const GLuint& Data_points, const GLuint& Data_dims, const std::vector<GLfloat>& Data);
	Model(const GLchar* XML_file_path);
	virtual ~Model();
	virtual inline void Model::add_attribute(const GLuint& Attrib_count)
	{
		Attributes.push_back(Attribute(Next_index++, Attrib_count, Points, Total_attribs));
		Total_attribs += Attrib_count;
	}
	virtual void buffer(const GLuint& VAO, const GLuint& VBO) const;
	virtual void draw();
protected:
	std::vector<Attribute> Attributes;
private:
	GLuint Total_attribs;
	GLuint Next_index;
};
#endif
