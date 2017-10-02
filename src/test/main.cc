#include<iostream>
#include"Graphics_sys.h"
#include"Model.h"
#include"Shader.h"
#include<vector>
const GLchar* VERT_FILE_PATH = "C:\\code\\shaders\\core.vs";
const GLchar* FRAG_FILE_PATH = "C:\\code\\shaders\\core.frag";
const GLchar* XML_FILE_PATH = "C:\\code\\xml\\Triangle.xml";
int main(int argc, char* argv[])
{
	Model m(XML_FILE_PATH);
	Graphics_sys::graphics_sys()->init_opengl();
	GLFWwindow* Window_ptr = Graphics_sys::graphics_sys()->create_window(800, 600, "Window");
	if (Window_ptr == nullptr)
	{
		std::cout << "window creation failed" << std::endl;
		throw std::runtime_error("window creation failed");
	}
	glfwMakeContextCurrent(Window_ptr);
	glewInit();
	glewExperimental = GL_TRUE;
	glEnable(GL_DEPTH_TEST);
	int sw, sh;
	glfwGetFramebufferSize(Window_ptr, &sw, &sh);
	glViewport(0, 0, sw, sh);
	Shader Graphics_shader;
	Graphics_shader.create_program(VERT_FILE_PATH, FRAG_FILE_PATH);
	
	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	m.add_attribute(3);
	m.buffer(vao, vbo);
	int Vertex_color_loc = glGetUniformLocation(Graphics_shader.get_program(), "Input_color");
	glUseProgram(Graphics_shader.get_program());
	glUniform4f(Vertex_color_loc, 0.5f, 0.5f, 0.5f, 1.0f);
	while (!glfwWindowShouldClose(Window_ptr))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		m.draw();
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glfwSwapBuffers(Window_ptr);
		glfwPollEvents();
	}
	return 0;
}