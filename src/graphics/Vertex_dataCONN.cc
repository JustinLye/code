#include "Vertex_dataCONN.h"

Vertex_dataCONN::Vertex_dataCONN() :
	Component_connector<Vertex_dataCMP, Vertex_dataCOMP>(),
	m_Point_count(~0)
{

}

Vertex_dataCONN::~Vertex_dataCONN()
{

}

void Vertex_dataCONN::fill_comp_data(const boost::property_tree::ptree& Prop_tree)
{
	m_Comps_data.clear();
	m_Attribs.clear();
	m_Point_count = ~0;
	unsigned int Next_attrib = 0;
	using namespace boost::property_tree;
	ptree::const_iterator Root = Prop_tree.begin();
	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Id = Root->second.get_value_optional<unsigned int>();
		if (!Id)
		{
			throw std::runtime_error("Possible malformed xml in config file: " + std::string(m_Config_fp));
		} else
		{
			auto Vect_cmp = m_Lookup_map.find(*Id);
			if (Vect_cmp == m_Lookup_map.end())
			{
				throw std::runtime_error("Id " + boost::lexical_cast<std::string>(*Id) + " not found.");
			}
			if (m_Point_count == ~0)
			{
				m_Point_count = Vect_cmp->second.count() / Vect_cmp->second.dimensions();
			} else if (m_Point_count != Vect_cmp->second.count() / Vect_cmp->second.dimensions())
			{
				throw std::runtime_error("Point count mismatch.");
			}
			m_Comps_data.push_back(Vect_cmp->second);
			m_Attribs.push_back(std::pair<unsigned int, unsigned int>(Next_attrib++, Vect_cmp->second.dimensions()));
		}
	}
}

void Vertex_dataCONN::connect_comp_data(const unsigned int& Id)
{
	for (std::size_t i = 0; i < m_Point_count; i++)
	{
		for (std::size_t v = 0; v < m_Comps_data.size(); v++)
		{
			for (std::size_t p = 0; p < m_Comps_data[v].Dimensions; p++)
			{
				m_Composite_map[Id].m_Point_data.push_back(m_Comps_data[v].Point_data[m_Comps_data[v].Index++]);
			}
		}
	}
	for (std::size_t i = 0; i < m_Comps_data.size(); i++)
	{
		m_Composite_map[Id].m_Attribs.push_back(std::pair<unsigned int, unsigned int>(i, m_Comps_data[i].Dimensions));
		m_Composite_map[Id].m_Dimensions += m_Comps_data[i].Dimensions;
	}
}

void Vertex_dataCONN::connect(const boost::property_tree::ptree& Prop_tree)
{
	using namespace boost::property_tree;
	m_Composite_map.clear();
	ptree::const_iterator Root = Prop_tree.begin();
	Vertex_dataCOMP Vert_cmp;
	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Id = Root->second.get_optional<unsigned int>("Id");
		boost::optional<const ptree&> Coord_ids = Root->second.get_child_optional("CoordIds");
		if (!Id || !Coord_ids)
		{
			throw std::runtime_error("Malformed xml in config file: " + std::string(m_Config_fp));
		}
		Vert_cmp.m_Id = *Id;
		m_Composite_map[*Id] = Vert_cmp;

		fill_comp_data(*Coord_ids);
		connect_comp_data(*Id);
	}


}