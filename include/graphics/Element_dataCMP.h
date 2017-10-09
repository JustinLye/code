#ifndef ELEMENT_DATACMP_H_INCLUDED
#define ELEMENT_DATACMP_H_INCLUDED
#include <vector>
#include "Component.h"

class Element_dataCMP : public Component
{
public:
	Element_dataCMP();
	virtual ~Element_dataCMP();
	std::size_t count() const
	{
		return m_Indices.size();
	}
	std::vector<unsigned int>& get_indices()
	{
		return m_Indices;
	}
protected:
	std::vector<unsigned int> m_Indices;
	friend class Element_dataBLDR;
};

#endif