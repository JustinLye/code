#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED
template<typename T>
class Component_builder;

class Component
{
public:
	
	Component();
	virtual ~Component();

	static const unsigned int NOT_AN_ID;

	inline const unsigned int& get_id() const
	{
		return m_Id;
	}
protected:
	unsigned int m_Id;
	friend class Component_builder<Component>;
};



#endif