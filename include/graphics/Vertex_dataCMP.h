#ifndef VERTEX_POINTCMP_H_INCLUDED
#define VERTEX_POINTCMP_H_INCLUDED
#include<vector>
#include<memory>
#include"Component.h"

class Vertex_dataCMP : public Component
{
public:
	Vertex_dataCMP();
	virtual ~Vertex_dataCMP();
	inline const std::size_t& count()
	{
		return m_Point_data.size();
	}
	// Access points directly
	std::vector<double>& get_point_data()
	{
		return m_Point_data;
	}
	inline const std::size_t& dimensions()
	{
		return m_Dimensions;
	}
protected:
	std::vector<double> m_Point_data;
	std::size_t m_Dimensions;
	friend class Vertex_dataBLDR;
};

#endif
