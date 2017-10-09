#include"Vertex_dataBLDR.h"

Vertex_dataBLDR::Vertex_dataBLDR() :
	Component_builder<Vertex_dataCMP>()
{

}

Vertex_dataBLDR::~Vertex_dataBLDR()
{

}

void Vertex_dataBLDR::process_point(const boost::property_tree::ptree& Prop_tree, const comp_id& Id)
{
	using namespace boost::property_tree;
	ptree::const_iterator Root = Prop_tree.begin();
	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_dbl Point = Root->second.get_value_optional<double>();
		if (!Point)
		{
			throw (("Malformed xml in config file: " + std::string(m_Config_fp)).c_str());
		}
		m_Point_queue.push(*Point);
	}
	push_back_point_data(Id);
}

void Vertex_dataBLDR::push_back_point_data(const comp_id& Id)
{
	if (m_Point_queue.size() != m_Component_map[Id].m_Dimensions)
	{
		throw std::runtime_error(("Point queue should contain " + boost::lexical_cast<std::string>(m_Component_map[Id].m_Dimensions) + (m_Component_map[Id].m_Dimensions <= 1 ? " point " : " points") + ", but " + boost::lexical_cast<std::string>(m_Point_queue.size()) + " points were found. Possible malformed xml in config file: " + std::string(m_Config_fp)).c_str());
	}
	while (!m_Point_queue.empty())
	{
		m_Component_map[Id].m_Point_data.push_back(m_Point_queue.front());
		m_Point_queue.pop();
	}
}

void Vertex_dataBLDR::build(const boost::property_tree::ptree& Prop_tree)
{
	using namespace boost::property_tree;
	m_Component_map.clear();
	Vertex_dataCMP Vert_cmp;
	ptree::const_iterator Root = Prop_tree.begin();

	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Id = Root->second.get_optional<comp_id>("Id");
		opt_uint Dimensions = Root->second.get_optional<unsigned int>("Dimensions");
		boost::optional<const ptree&> Sub_root = Root->second.get_child_optional("Points");
		if (!Id || !Dimensions || !Sub_root)
		{
			throw std::runtime_error(("Malformed xml in config file: " + std::string(m_Config_fp)).c_str());
		}
		Vert_cmp.m_Id = *Id;
		Vert_cmp.m_Dimensions = *Dimensions;
		m_Component_map[*Id] = Vert_cmp;
		ptree::const_iterator Point_root = Sub_root->begin();
		for (Point_root; Point_root != Sub_root->end(); Point_root++)
		{
			process_point(Point_root->second, *Id);
		}
	}
}