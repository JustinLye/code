#include "Element_dataBLDR.h"

Element_dataBLDR::Element_dataBLDR() :
	Component_builder<Element_dataCMP>()
{

}

Element_dataBLDR::~Element_dataBLDR()
{

}

void Element_dataBLDR::process_indice(const boost::property_tree::ptree& Prop_tree, const comp_id& Id)
{
	using namespace boost::property_tree;
	ptree::const_iterator Root = Prop_tree.begin();
	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Index = Root->second.get_value_optional<unsigned int>();
		if (!Index)
		{
			throw std::runtime_error("Malformed xml in config file: " + std::string(m_Config_fp));
		}
		m_Index_queue.push(*Index);
	}
	push_back_index_data(Id);
}

void Element_dataBLDR::push_back_index_data(const comp_id& Id)
{
	while (!m_Index_queue.empty())
	{
		m_Component_map[Id].m_Indices.push_back(m_Index_queue.front());
		m_Index_queue.pop();
	}
}

void Element_dataBLDR::build(const boost::property_tree::ptree& Prop_tree)
{
	using namespace boost::property_tree;
	ptree::const_iterator Root = Prop_tree.begin();
	Element_dataCMP Elem_cmp;

	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Id = Root->second.get_optional<unsigned int>("Id");
		boost::optional<const ptree&> Sub_root = Root->second.get_child_optional("Indices");
		if (!Id || !Sub_root)
		{
			throw std::runtime_error("Malformed xml in config file: " + std::string(m_Config_fp));
		}
		else if (m_Component_map.find(*Id) != m_Component_map.end())
		{
			throw std::runtime_error("Id " + boost::lexical_cast<std::string>(*Id) + " has already been mapped to a component.");
		}
		Elem_cmp.m_Id = *Id;
		m_Component_map[*Id] = Elem_cmp;
		process_indice(*Sub_root, *Id);
	}

}