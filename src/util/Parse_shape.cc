#include"Parse_shape.h"

Shape_data_pack::Shape_data_pack() :
	Total_data_points(0),
	Total_dimensions(0),
	Data_points(std::vector<GLfloat>()),
	Has_position_data(false),
	Has_color_data(false),
	Has_texture_data(false)
{
}

Parse_shape* Parse_shape::Instance_ptr = nullptr;

Parse_shape* Parse_shape::instance()
{
	if (Instance_ptr == nullptr)
		Instance_ptr = new Parse_shape;
	return Instance_ptr;
}

Shape_data_pack Parse_shape::parse_shape_data(const GLchar* XML_file_path)
{
	std::lock_guard<std::mutex> Locker(Parsing_mtx);
	using namespace boost::property_tree;
	Shape_data_pack Data_pack;
	std::ifstream XML_file;
	XML_file.open(XML_file_path);
	if (!XML_file)
	{
		throw std::runtime_error("Failure to open XML file.");
	}
	ptree Shape_tree;
	xml_parser::read_xml(XML_file, Shape_tree);
	ptree& Points = Shape_tree.get_child(ptree::path_type("Shape"));

	std::size_t Temp_dim_count = 0;

	for (auto Point : Points)
	{
		if (Point.first == "DataPoint")
		{
			Data_pack.Total_data_points++;
			if (boost::optional<ptree&> Positions = Point.second.get_child_optional(ptree::path_type("Position")))
			{
				for (auto Pos : *Positions)
				{
					++Temp_dim_count;
					Data_pack.Data_points.push_back(Pos.second.get_value<GLfloat>());
				}
			}
			if (boost::optional<ptree&> Colors = Point.second.get_child_optional(ptree::path_type("Color")))
			{
				for (auto Color : *Colors)
				{
					++Temp_dim_count;
					Data_pack.Data_points.push_back(Color.second.get_value<GLfloat>());
				}
			}
			if (boost::optional<ptree&> TexCoords = Point.second.get_child_optional(ptree::path_type("TextureCoord")))
			{
				for (auto TexCoord : *TexCoords)
				{
					++Temp_dim_count;
					Data_pack.Data_points.push_back(TexCoord.second.get_value<GLfloat>());
				}
			}
			if (Data_pack.Total_dimensions == 0)
			{
				Data_pack.Total_dimensions = Temp_dim_count;
			}
			else if (Data_pack.Total_dimensions != Temp_dim_count)
			{
				throw std::runtime_error("Dimension count mismatch.");
			}
			Temp_dim_count = 0;
		}
	}
	return Data_pack;
}