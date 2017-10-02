#include"Shape.h"

Shape::Shape() :
	Points(0),
	Dimensions(0),
	Point_data(nullptr),
	Data_pack(Shape_data_pack())
{

}

Shape::Shape(const GLuint& Data_points, const GLuint& Data_dims, const GLfloat* Data) :
	Points(Data_points),
	Dimensions(Data_dims),
	Point_data(nullptr),
	Data_pack(Shape_data_pack())
{
	Point_data = new GLfloat[Points * Dimensions];
	for (GLuint i = 0; i < (Points * Dimensions); i++)
		Point_data[i] = Data[i];
}

Shape::Shape(const GLuint& Data_points, const GLuint& Data_dims, const std::vector<GLfloat>& Data) :
	Points(Data_points),
	Dimensions(Data_dims),
	Point_data(nullptr),
	Data_pack(Shape_data_pack())

{
	Point_data = new GLfloat[Points * Dimensions];
	for (GLuint i = 0; i < (Points * Dimensions); i++)
		Point_data[i] = Data[i];
}

Shape::Shape(const GLchar* XML_file_path) :
	Points(0),
	Dimensions(0),
	Point_data(nullptr),
	Data_pack(Shape_data_pack())
{
	Parse_shape* Parser = Parse_shape::instance();
	Data_pack = Parser->parse_shape_data(XML_file_path);
	Points = Data_pack.Total_data_points;
	Dimensions = Data_pack.Total_dimensions;
	Point_data = new GLfloat[Points * Dimensions];
	for (GLuint i = 0; i < (Points * Dimensions); i++)
	{
		Point_data[i] = Data_pack.Data_points[i];
	}
}

Shape::~Shape()
{
	if (Point_data != nullptr)
		delete[] Point_data;
}

// Sets data to be used by the shape
void Shape::set_data(const GLuint& Data_points, const GLuint& Data_dims, const GLfloat* Data)
{
	Points = Data_points;
	Dimensions = Data_dims;
	if (Point_data != nullptr)
		delete[] Point_data;
	Point_data = new GLfloat[Points * Dimensions];
	for (GLuint i = 0; i < (Points * Dimensions); i++)
		Point_data[i] = Data[i];
}

