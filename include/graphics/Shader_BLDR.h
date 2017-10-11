#ifndef SHADER_BLDR_H_INCLUDED
#define SHADER_BLDR_H_INCLUDED

#include "Shader_COMP.h"
#include "Component_builder.h"

class Shader_BLDR : public Component_builder<Shader_COMP>
{
public:
	Shader_BLDR();
	virtual ~Shader_BLDR();
	void set_shader_map(const std::map<unsigned int, Shader_progCMP>& Shader_lookup_map)
	{
		m_Shader_lookup_map = Shader_lookup_map;
	}
	void set_texture2D_map(const std::map<unsigned int, Texture2D_CMP> Texture2D_lookup_map)
	{
		m_Texture_lookup_map = Texture2D_lookup_map;
	}
protected:
	std::map<unsigned int, Shader_progCMP> m_Shader_lookup_map; // Holds shader components that have already been created
	std::map<unsigned int, Texture2D_CMP> m_Texture_lookup_map; // Holds texture2D componets that have been created and loaded
	virtual void add_textures(const boost::property_tree::ptree& Prop_tree, const comp_id& Id);
	virtual void build(const boost::property_tree::ptree& Prop_tree);

};

#endif