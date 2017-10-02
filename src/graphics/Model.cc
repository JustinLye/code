#include"Model.h"

Model::Model() :
	Shape(),
	Total_attribs(0),
	Next_index(0)

{

}

Model::Model(const GLuint& Data_points, const GLuint& Data_dims, const GLfloat* Data) :
	Shape(Data_points, Data_dims, Data),
	Total_attribs(0),
	Next_index(0)
{

}

Model::Model(const GLuint& Data_points, const GLuint& Data_dims, const std::vector<GLfloat>& Data) :
	Shape(Data_points, Data_dims, Data),
	Total_attribs(0),
	Next_index(0)
{

}

Model::Model(const GLchar* XML_file_path) :
	Shape(XML_file_path),
	Total_attribs(0),
	Next_index(0)
{
	if (Data_pack.Has_position_data)
	{
		add_attribute(3);
	}
	if (Data_pack.Has_color_data)
	{
		add_attribute(3);
	}
	if (Data_pack.Has_texture_data)
	{
		add_attribute(2);
	}
}

Model::~Model()
{

}

void Model::buffer(const GLuint& VAO, const GLuint& VBO) const
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*(Dimensions * Points), Point_data, GL_STATIC_DRAW);
	for (auto i : Attributes)
	{
		glVertexAttribPointer(
			i.Index,
			i.Count,
			GL_FLOAT,
			GL_FALSE,
			Dimensions * sizeof(GLfloat),
			(GLvoid*)(i.Offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(i.Index);
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Points);
}