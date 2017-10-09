#include"Texture_imageBLDR.h"

Texture_imageBLDR::Texture_imageBLDR() :
	Component_builder<Texture_imageCMP>()
{
}

Texture_imageBLDR::~Texture_imageBLDR()
{

}

void Texture_imageBLDR::build(const boost::property_tree::ptree& Prop_tree)
{
	using namespace boost::property_tree;
	m_Component_map.clear();	// remove any existing components that may be in the map
	Texture_imageCMP Img_comp;  // Image component used to store values and copy to the map
	ptree::const_iterator Root = Prop_tree.begin();

	for (Root; Root != Prop_tree.end(); Root++)
	{
		boost::optional<comp_id> Id = Root->second.get_optional<comp_id>("Id");
		boost::optional<std::string> Image_fp = Root->second.get_optional<std::string>("ImageFilePath");
		if (!Id || !Image_fp)
		{
			throw std::runtime_error("Malformed xml in config file: " + std::string(m_Config_fp));
		}
		else if (m_Component_map.find(*Id) != m_Component_map.end())
		{
			throw std::runtime_error(("Duplicate ids found in config file " + std::string(m_Config_fp)).c_str());
		}

		Img_comp.m_Image_fp = *Image_fp;
		Img_comp.m_Id = *Id;

		m_Component_map[*Id] = Img_comp;
	}

}