#ifndef TEXTURE_DATACMP_H_INCLUDED
#define TEXTURE_DATACMP_H_INCLUDED

#include<memory>
#include<vector>
#include"Component.h"

class Texture_dataCMP : public Component
{
public:
	Texture_dataCMP();
	virtual ~Texture_dataCMP();
	inline const std::size_t& count()
	{
		return m_Point_data.size();
	}

protected:
};

#endif