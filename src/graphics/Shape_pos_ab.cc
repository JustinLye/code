#include "Shape_pos_ab.h"

Shape_pos_ab::Shape_pos_ab(const GLchar* XML_config_fp) :
	Structured_shape(),
	m_Gen_buffs_flag(true),
	m_VAO(0),
	m_VBO(0)
{
	if (XML_config_fp != nullptr)
	{
		configure(XML_config_fp);
	}
}

Shape_pos_ab::~Shape_pos_ab()
{
	if (!m_Gen_buffs_flag)
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);	
	}
}

void Shape_pos_ab::configure_shape(const GLchar* XML_config_fp)
{
	using namespace boost::property_tree;
	using namespace boost::property_tree::xml_parser;
	using namespace cfg::xml::paths;

	std::ifstream XML_file;
	XML_file.open(XML_config_fp); // Attempt to open file
	if (!XML_file)
	{
		throw std::runtime_error("Failure occurred opening shape configuration file."); // Throw exception if bad config file
	}
	
	ptree Config_data; // Top-level property tree
	read_xml(XML_file, Config_data); // Read-in xml file

	configure_shape(Config_data);
}

void Shape_pos_ab::configure_shape(boost::property_tree::ptree& XML_data)
{
	using namespace boost::property_tree;
	using namespace boost::property_tree::xml_parser;
	using namespace cfg::xml::paths;

	boost::optional<ptree&> Shape = XML_data.get_child_optional(XML_ELEM_SHAPE);
}