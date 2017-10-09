#ifndef VERTEX_DATACONN_H_INCLUDED
#define VERTEX_DATACONN_H_INCLUDED
#include <vector>
#include <boost/lexical_cast.hpp>
#include "Vertex_dataCMP.h"
#include "Component_connector.h"

class Vertex_dataCONN : public Component_connector<Vertex_dataCMP, Vertex_dataCMP>
{
public:
	Vertex_dataCONN();
	virtual ~Vertex_dataCONN();

protected:
	struct Comp_data
	{
		std::size_t Index;
		std::size_t Dimensions;
		const std::vector<double>& Point_data;
		Comp_data() :
			Index(0),
			Dimensions(0),
			Point_data(std::vector<double>())
		{

		}
		Comp_data(const Vertex_dataCMP& Vertex_data) :
			Index(0),
			Dimensions(Vertex_data.m_Dimensions),
			Point_data(Vertex_data.m_Point_data)
		{

		}
	};
	std::vector<Comp_data> m_Comps_data;
	std::size_t m_Point_count;
	virtual void fill_comp_data(const boost::property_tree::ptree& Prop_tree);
	virtual void connect_comp_data(const unsigned int& Id);
	virtual void connect(const boost::property_tree::ptree& Prop_tree);
};

#endif