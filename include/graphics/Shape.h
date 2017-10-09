#ifndef __SHAPE_H_INCLUDED__
#define __SHAPE_H_INCLUDED__

// Shapes are simple geometric objects

#include"Graphics_sys.h" //for opengl headers
#include"Component.h"
#include<vector>
class Shape : public Component
{
public:
	Shape();
	virtual ~Shape();
	virtual void configure(const GLchar* XML_config_fp);
	virtual void buffer();
	virtual void draw();
protected:
	
	std::vector<GLfloat> m_Data_points; // This array contains all information that will be used to render the shape
	bool m_Rebuffer_flag; // This flag is intended to be set to true if the shape should be buffered before the next call to draw(). Used by draw as sanity check. Is set to true by configure()
	bool m_Configured_flag; // This flag is used to check if a configuration has been performed. Used by buffer() as a sort of sanity check.
	
	virtual void configure_shape(const GLchar* XML_config_fp) = 0;
	virtual void buffer_shape() = 0;
	virtual void draw_shape() = 0;
};

#endif