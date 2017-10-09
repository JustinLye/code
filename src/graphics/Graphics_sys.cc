#include"Graphics_sys.h"

Graphics_sys* Graphics_sys::Instance_ptr = nullptr;

Graphics_sys::Graphics_sys() :
Is_initialized(false),
m_Log("Graphics_sys.log")
{
	m_Log.log_message(INFO_MESSAGE("Graphics system constructed."));
}

Graphics_sys::~Graphics_sys()
{
    // Terminate GLFW if needed
    if (Is_initialized)
    {
		m_Log.log_message(INFO_MESSAGE("Graphics system: terminating GLFW."));
        glfwTerminate();
    }
	m_Log.log_message(INFO_MESSAGE("Graphics system destructed."));
}

Graphics_sys* Graphics_sys::graphics_sys()
{
    if (!Instance_ptr)
    {
        Instance_ptr = new Graphics_sys;
    }
    return Instance_ptr;
}

void Graphics_sys::init_opengl()
{
	std::lock_guard<std::mutex> Locker(Init_mtx); // lock thread 
    if (Is_initialized)
    {
        m_Log.log_message(INFO_MESSAGE("Warning! No action taken. Graphics system already initialized"));
        return;
    }
	
    if (glfwInit() != GLFW_TRUE)
    {
        m_Log.log_message(APP_ERROR_MESSAGE("System failure occurred! System could not be initialized"));
        throw std::runtime_error("System could not be initialized.");
    }
	m_Log.log_message(INFO_MESSAGE("GLFW successfully initilalized."));
	Is_initialized = true;

}

GLFWwindow* Graphics_sys::create_window(const GLuint& Width, const GLuint& Height, const GLchar* Title)
{
	if (!Is_initialized)
	{
		m_Log.log_message(INFO_MESSAGE("Warning! No action taken. Graphics system not yet initilalized"));
		return nullptr;
	}
	m_Log.log_message(INFO_MESSAGE("Creating window."));
	GLFWwindow* Window_ptr = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
	if (!Window_ptr)
	{
		m_Log.log_message(APP_ERROR_MESSAGE("Failed to create window."));
		return nullptr;
	}

	m_Log.log_message(INFO_MESSAGE("Window created"));
	return Window_ptr;
}

void Graphics_sys::set_hint(int Window_hint, int Value)
{
	m_Log.log_message(INFO_MESSAGE("Adding window hint"));
    glfwWindowHint(Window_hint, Value);
}

void Graphics_sys::set_hint(const std::vector<std::pair<int,int>>& Hints)
{
    for (auto h : Hints)
    {
        glfwWindowHint(h.first, h.second);
    }
}
