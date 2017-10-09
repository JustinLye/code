#include"Vertex_dataCMP.h"

Vertex_dataCMP::Vertex_dataCMP() :
	Component()
{

}

Vertex_dataCMP::~Vertex_dataCMP()
{

}

std::shared_ptr<double> Vertex_dataCMP::get_data_ptr()
{
	if (!m_Data_ptr)
	{
		m_Data_ptr = std::shared_ptr<double>(new double[m_Point_data.size() * 3], [](double* Dbl_ptr) { delete[] Dbl_ptr; });
		std::size_t Data_ptr_i = 0;
		for (auto i : m_Point_data)
		{
			m_Data_ptr.get()[Data_ptr_i++] = i.x;
			m_Data_ptr.get()[Data_ptr_i++] = i.y;
			m_Data_ptr.get()[Data_ptr_i++] = i.z;
		}
	}
	return m_Data_ptr;
}