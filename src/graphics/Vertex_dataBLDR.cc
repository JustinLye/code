#include"Vertex_dataBLDR.h"

Vertex_dataBLDR::Vertex_dataBLDR() :
	Component_builder<Vertex_dataCMP>()
{

}

Vertex_dataBLDR::~Vertex_dataBLDR()
{

}

Point_data<double> Vertex_dataBLDR::process_point(const boost::property_tree::ptree& Prop_tree)
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
	return create_point_data();
}

Point_data<double> Vertex_dataBLDR::create_point_data()
{
	if (m_Point_queue.size() != 3)
	{
		throw std::runtime_error(("Point queue should contain 3 points. Possible malformed xml in config file: " + std::string(m_Config_fp)).c_str());
	}
	Point_data<double> Result_data;
	Result_data.x = m_Point_queue.front();
	m_Point_queue.pop();
	Result_data.y = m_Point_queue.front();
	m_Point_queue.pop();
	Result_data.z = m_Point_queue.front();
	m_Point_queue.pop();
	return Result_data;
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
		boost::optional<const ptree&> Sub_root = Root->second.get_child_optional("Points");
		if (!Id || !Sub_root)
		{
			throw std::runtime_error(("Malformed xml in config file: " + std::string(m_Config_fp)).c_str());
		}
		Vert_cmp.m_Id = *Id;
		m_Component_map[*Id] = Vert_cmp;
		Point_data<double> Vert_data;
		ptree::const_iterator Point_root = Sub_root->begin();
		for (Point_root; Point_root != Sub_root->end(); Point_root++)
		{
			m_Component_map[*Id].m_Point_data.push_back(process_point(Point_root->second));
			if (!m_Point_queue.empty())
			{
				throw std::runtime_error(("Point queue should be empty. Possible malformed xml in config file: " + std::string(m_Config_fp)).c_str());
			}
		}
	}
}