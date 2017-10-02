#ifndef __CONTEXT_H_INCLUDED__
#define __CONTEXT_H_INCLUDED__
#include <vector>
#include "Graphics_sys.h"
#include "Thread.h"
class Context :
	public Thread
{
public:
	explicit Context(GLuint Width = 800, GLuint Height = 600, const GLchar* Title = "Window");
protected: 
	virtual void entry_point();
	virtual void init_sys();
	virtual void create_window();
private:
	GLint Window_width;
	GLint Window_height;
	const GLchar* Window_title;
	GLFWwindow* Window_ptr;
	Graphics_sys* Graphics;
	jl::Log_file Log;

};

#endif

