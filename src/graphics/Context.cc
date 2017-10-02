#include"Context.h"

Context::Context(GLuint Width, GLuint Height, const GLchar* Title) :
	Thread(),
	Window_width(Width),
	Window_height(Height),
	Window_title(Title),
	Window_ptr(nullptr),
	Graphics(Graphics_sys::graphics_sys()),
	Log("Context.log")
{
	Log.log_message(INFO_MESSAGE("Context constructed."));
}

void Context::entry_point()
{
	Log.log_message(INFO_MESSAGE("entry_point() called."));
	Log.log_message(INFO_MESSAGE("Initalizing graphics system."));
	init_sys();
	Log.log_message(INFO_MESSAGE("Graphics system initialized."));
	Log.log_message(INFO_MESSAGE("Attempting to create window."));
	create_window();
	Log.log_message(INFO_MESSAGE("Window created."));
}

void Context::init_sys()
{
	Log.log_message(INFO_MESSAGE("Setting default window hints."));
	Graphics->set_hint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	Graphics->set_hint(GLFW_CONTEXT_VERSION_MINOR, 3);
	Graphics->set_hint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Graphics->init_opengl();
}

void Context::create_window()
{
	Log.log_message(INFO_MESSAGE("Attempting to create window."));
	Window_ptr = Graphics->create_window(Window_width, Window_height, Window_title);
	if (Window_ptr == nullptr)
	{
		Log.log_message(APP_ERROR_MESSAGE("Window creation failed."));
		throw std::runtime_error("Failed to create window.");
	}
	Log.log_message(INFO_MESSAGE("Setting GLFW context."));
	glfwMakeContextCurrent(Window_ptr);
	Log.log_message(INFO_MESSAGE("Initializing glew"));
	if (glewInit() != GLEW_OK)
	{
		Log.log_message(APP_ERROR_MESSAGE("Failed to initialize GLEW"));
		throw std::runtime_error("Failure occurred initializing GLEW");
	}
	glewExperimental = GL_TRUE;
	glEnable(GL_DEPTH_TEST);
	int Screen_width, Screen_height;
	glfwGetFramebufferSize(Window_ptr, &Screen_width, &Screen_height);
	glViewport(0, 0, Screen_width, Screen_height);
	Log.log_message(INFO_MESSAGE("Window successfully created."));
}