#ifndef VERTEX_POINTCMP_H_INCLUDED
#define VERTEX_POINTCMP_H_INCLUDED
#include<vector>
#include<memory>
#include"Component.h"

template<typename T>
struct Point_data
{
	T x;
	T y;
	T z;
	Point_data() {}
	Point_data(T Value) :
		x(Value),
		y(Value),
		z(Value)
	{
	}
	Point_data(T X_val, T Y_val, T Z_val) :
		x(X_val),
		y(Y_val),
		z(Z_val)
	{
	}
};

class Vertex_dataCMP : public Component
{
public:
	Vertex_dataCMP();
	virtual ~Vertex_dataCMP();
	virtual std::shared_ptr<double> get_data_ptr();
	inline const std::size_t& count()
	{
		return m_Point_data.size();
	}
	std::vector<Point_data<double>> get_point_data() const
	{
		return m_Point_data;
	}
protected:
	std::vector<Point_data<double>> m_Point_data;
	std::shared_ptr<double> m_Data_ptr;
	friend class Vertex_dataBLDR;
};

#endif
