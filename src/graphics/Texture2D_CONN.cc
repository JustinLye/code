#include "Texture2D_CONN.h"

Texture2D_CONN::Texture2D_CONN() :
	Component_connector<Texture_imageCMP, Texture2D_CMP>()
{

}

Texture2D_CONN::~Texture2D_CONN()
{

}

void Texture2D_CONN::connect(const boost::property_tree::ptree& Prop_tree)
{
	using namespace boost::property_tree;
	ptree::const_iterator Root = Prop_tree.begin();
	Texture2D_CMP Tex_cmp;

	for (Root; Root != Prop_tree.end(); Root++)
	{
		opt_uint Id = Root->second.get_optional<unsigned int>("Id");
		opt_uint Img_cmp_id = Root->second.get_optional<unsigned int>("ImgCmpId");
		opt_uint Act_tex_offset = Root->second.get_optional<unsigned int>("ActiveTexOffset");
		auto Img_cmp = m_Lookup_map.find(*Img_cmp_id);
		if (!Id || !Img_cmp_id || !Act_tex_offset)
		{
			throw std::runtime_error("Malformed xml in config file: " + std::string(m_Config_fp));
		}
		else if (Img_cmp == m_Lookup_map.end())
		{
			throw std::runtime_error("Image component id " + boost::lexical_cast<std::string>(*Img_cmp_id) + " is not in lookup map");
		}
		else if (m_Composite_map.find(*Id) != m_Composite_map.end())
		{
			throw std::runtime_error("Id " + boost::lexical_cast<std::string>(*Id) + " is already mapped to a texture composition");
		}
		Tex_cmp.m_Id = *Id;
		Tex_cmp.m_Unit_offset = *Act_tex_offset;
		Tex_cmp.m_Image_fp = Img_cmp->second.get_image_fp();
		m_Composite_map[*Id] = Tex_cmp;
		m_Composite_map[*Id].load();
	}


}