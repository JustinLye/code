#ifndef __GRAPHICS_SYS_H_INCLUDED__
#define __GRAPHICS_SYS_H_INCLUDED__


#define GLEW_STATIC

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#define STD_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include<vector>
#include"Log_file.h"

using namespace jl;

//Singleton class for initialization
class Graphics_sys
{
public:
    void init_opengl();
	GLFWwindow* create_window(const GLuint& Width, const GLuint& Height, const GLchar* Title);
    void set_hint(int Window_hint, int Value);
    void set_hint(const std::vector<std::pair<int,int>>& Hints);
    static Graphics_sys* graphics_sys(); ///< Get pointer to class instance
private:
    //Singleton has private constructors
    Graphics_sys();
    Graphics_sys(const Graphics_sys&) : m_Log("Graphics_sys.log") {}
    Graphics_sys(Graphics_sys&&) : m_Log("Graphics_sys.log") {}
    ~Graphics_sys();

    static Graphics_sys* Instance_ptr;
    bool Is_initialized; ///< Used to check if opengl has been initiated
	bool Glew_is_init; ///< Used to check if glew is initiated
	std::mutex Init_mtx;
    Log_file m_Log;
};


#endif