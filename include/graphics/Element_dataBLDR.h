#ifndef ELEMENT_DATABLDR_H_INCLUDED
#define ELEMENT_DATABLDR_H_INCLUDED
#include <queue>
#include <boost/lexical_cast.hpp>
#include "Component_builder.h"
#include "Element_dataCMP.h"

class Element_dataBLDR : public Component_builder<Element_dataCMP>
{
public:
	Element_dataBLDR();
	virtual ~Element_dataBLDR();
protected:
	std::queue<unsigned int> m_Index_queue;
	virtual void process_indice(const boost::property_tree::ptree& Prop_tree, const comp_id& Id);
	virtual void push_back_index_data(const comp_id& Id);
	virtual void build(const boost::property_tree::ptree& Prop_tree);
};

#endif