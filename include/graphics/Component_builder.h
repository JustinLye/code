
#ifndef __COMPONENT_BUILDER_H_INCLUDED__
#define __COMPONENT_BUILDER_H_INCLUDED__
#include<stdexcept>
#include<fstream>
#include<map>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
#include"Log_file.h"

template<typename T>
class Component_builder
{
public:
	typedef unsigned int comp_id;
	typedef boost::optional<comp_id> opt_uint;
	typedef boost::optional<std::string> opt_str;
	typedef boost::optional<double> opt_dbl;
	Component_builder<T>();
	virtual ~Component_builder<T>()
	{

	}
	virtual std::map<comp_id, T> build_map(const char* Config_fp = nullptr)
	{
		if (Config_fp != nullptr)
		{
			m_Config_fp = Config_fp;
		}

		return operator()();
	}
	virtual std::map<comp_id, T> operator()()
	{
		if (m_Config_fp == nullptr)
		{
			throw std::runtime_error("Component cannot be built without a configuration file.");
		}
		build_components();
		return m_Component_map;
	}
	
	virtual void set_config(const char* Config_fp)
	{
		m_Config_fp = Config_fp;
	}
	virtual const char* get_config() const
	{
		return m_Config_fp;
	}
protected:
	const char* m_Config_fp;
	std::map<comp_id, T> m_Component_map;

	virtual void build_components();
	virtual void build(const boost::property_tree::ptree& Prop_tree) = 0;
};

//#include"Component_builder.cc"

template<typename T>
Component_builder<T>::Component_builder() :
	m_Config_fp(nullptr)
{
}

template<typename T>
void Component_builder<T>::build_components()
{

	std::ifstream Config_file;
	Config_file.open(m_Config_fp);

	if (!Config_file)
	{
		throw std::runtime_error("Config file could not be opened.");
	}

	boost::property_tree::ptree Prop_tree;
	boost::property_tree::xml_parser::read_xml(Config_file, Prop_tree);
	build(Prop_tree);
}

#endif