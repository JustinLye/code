#ifndef COMPONENT_CONNECTOR_H_INCLUDED
#define COMPONENT_CONNECTOR_H_INCLUDED

#include <stdexcept>
#include <fstream>
#include <string>
#include "typedefs.h"

template<typename Component_type, typename Composite_type>
class Component_connector
{
public:
	Component_connector();
	virtual ~Component_connector()
	{

	}
	void set_config(const char* Config_fp)
	{
		m_Config_fp = Config_fp;
	}
	void set_lookup_map(const std::map<unsigned int, Component_type>& Component_lookup_map)
	{
		m_Lookup_map = Component_lookup_map;
	}
	std::map<unsigned int, Composite_type> build_map(std::map<unsigned int, Component_type>& Component_lookup_map, const char* Config_fp = nullptr)
	{
		if (Config_fp != nullptr)
		{
			m_Config_fp = Config_fp;
		}
		m_Lookup_map = Component_lookup_map;
		return operator()();
	}
	std::map<unsigned int, Composite_type> operator()()
	{
		if (m_Config_fp == nullptr)
		{
			throw std::runtime_error("Configuration file not set");
		}
		if (m_Lookup_map.empty())
		{
			throw std::runtime_error("Component lookup map cannot be empty.");
		}
		connect_components();
		return m_Composite_map;
	}
protected:
	const char* m_Config_fp;
	std::map<unsigned int, Component_type> m_Lookup_map;
	std::map<unsigned int, Composite_type> m_Composite_map;

	virtual void connect_components();
	virtual void connect(const boost::property_tree::ptree& Prop_tree) = 0;

};

template<typename Component_type, typename Composite_type>
Component_connector<Component_type, Composite_type>::Component_connector() :
	m_Config_fp(nullptr)
{

}

template<typename Component_type, typename Composite_type>
void Component_connector<Component_type, Composite_type>::connect_components()
{
	std::ifstream Config_file;
	Config_file.open(m_Config_fp);

	if (!Config_file)
	{
		throw std::runtime_error("Config file could not be opened" + std::string(m_Config_fp));
	}

	boost::property_tree::ptree Prop_tree;
	boost::property_tree::xml_parser::read_xml(Config_file, Prop_tree);
	connect(Prop_tree);
}

#endif