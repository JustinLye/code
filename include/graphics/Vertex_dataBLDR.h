#ifndef VERTEX_DATABLDR_H_INCLUDED
#define VERTEX_DATABLDR_H_INCLUDED
#include <queue>
#include"Component_builder.h"
#include"Vertex_dataCMP.h"

class Vertex_dataBLDR : public Component_builder<Vertex_dataCMP>
{
public:
	Vertex_dataBLDR();
	virtual ~Vertex_dataBLDR();
protected:
	std::queue<double> m_Point_queue;
	virtual Point_data<double> process_point(const boost::property_tree::ptree& Prop_tree);
	virtual Point_data<double> create_point_data();
	virtual void build(const boost::property_tree::ptree& Prop_tree);
};

#endif