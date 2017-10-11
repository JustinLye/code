#include "Shader_BLDR.h"

Shader_BLDR::Shader_BLDR() :
	Component_builder<Shader_COMP>()
{

}

Shader_BLDR::~Shader_BLDR()
{

}

void Shader_BLDR::add_textures(const boost::property_tree::ptree& Prop_tree, const comp_id& Id)
{
	// Assign textures in tree to the shader component mapped to Id
	// The config file communicates what Texture2D_CMP to use via that
	// Texture2D_CMP's Id.
	// The texture tree should have a depth of 1, 
	// each child element being the Id of a Texture2D_CMP

	using namespace boost::property_tree;
	ptree::const_iterator Root = Prop_tree.begin(); // get the root of the tree

	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Texture_id = Root->second.get_value_optional<unsigned int>(); // get the next id in the tree
		// check if the id was retrieved and exists in the texture lookup map
		if (!Texture_id)
		{
			throw std::runtime_error(m_Malformed_error_msg);
		}
		else if (m_Texture_lookup_map.find(*Texture_id) == m_Texture_lookup_map.end())
		{
			throw std::runtime_error("Id " + boost::lexical_cast<std::string>(*Texture_id) + " was not found in the texture lookup map.");
		}
		// push the entire Texture2D_CMP into the shader components vector of texture2d components
		m_Component_map[Id].m_Textures.push_back(m_Texture_lookup_map[*Texture_id]);
	}
}

void Shader_BLDR::build(const boost::property_tree::ptree& Prop_tree)
{
	using namespace boost::property_tree;
	ptree::const_iterator Root = Prop_tree.begin();
	Shader_COMP Shader_cmp;
	
	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Id = Root->second.get_optional<unsigned int>("Id"); // Id of Shader_COMP
		// check the if Id is valid and exists
		if (!Id)
		{
			throw std::runtime_error(m_Malformed_error_msg);
		}
		else if (m_Component_map.find(*Id) != m_Component_map.end)
		{
			throw std::runtime_error(existing_id_error_msg(*Id));
		}
		opt_uint Shader_id = Root->second.get_optional<unsigned int>("ShaderProgId"); // lookup the id of the Shader_progCMP
		// check if the Shader_id is valid and exists
		if (!Shader_id)
		{
			throw std::runtime_error(m_Malformed_error_msg);
		}
		else if (m_Shader_lookup_map.find(*Shader_id) == m_Shader_lookup_map.end())
		{
			throw std::runtime_error("Id " + boost::lexical_cast<std::string>(*Id) + " was not found in the Shader lookup map.");
		}
		// Assign Id and shader program id to the shader component, then insert the shader component into the map
		Shader_cmp.m_Id = *Id;
		Shader_cmp.m_Shader_prog_id = m_Shader_lookup_map[*Shader_id].get_id();

		// attempt to retrieve textures child element from property tree
		boost::optional<const ptree&> Texture_tree = Root->second.get_child_optional("Textures");

		// if textures where found, added them to the shader component via sub-routine
		if (Texture_tree)
		{
			add_textures(*Texture_tree, *Id);
		}
	}
}