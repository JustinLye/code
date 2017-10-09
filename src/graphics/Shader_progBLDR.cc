#include "Shader_progBLDR.h"

Shader_progBLDR::Shader_progBLDR() :
	Component_builder<Shader_progCMP>()
{

}

Shader_progBLDR::~Shader_progBLDR()
{

}

void Shader_progBLDR::build(const boost::property_tree::ptree& Prop_tree)
{
	using namespace boost::property_tree;
	m_Component_map.clear();
	Shader_progCMP Shad_cmp;
	ptree::const_iterator Root = Prop_tree.begin();

	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Id = Root->second.get_optional<comp_id>("Id");
		opt_str Vert_fp = Root->second.get_optional<std::string>("VertexFilePath");
		opt_str Frag_fp = Root->second.get_optional<std::string>("FragmentFilePath");
		if (!Id || !Vert_fp || !Frag_fp)
		{
			throw std::runtime_error("Malformed xml in config file: " + std::string(m_Config_fp));
		}
		else if (m_Component_map.find(*Id) != m_Component_map.end())
		{
			throw std::runtime_error(("Duplicate ids found in config file " + std::string(m_Config_fp)).c_str());
		}

		Shad_cmp.m_Id = *Id;
		Shad_cmp.m_Vert_fp = *Vert_fp;
		Shad_cmp.m_Frag_fp = *Frag_fp;
		m_Component_map[*Id] = Shad_cmp;
	}
}