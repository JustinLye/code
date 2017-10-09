#include"Shader.h"

Shader::Shader() :
	m_Log("Shader.log")
{
	m_Log.log_message(INFO_MESSAGE("Shader constructed."));
}

void Shader::create_program(const GLchar* Vertex_shader_path, const GLchar* Frag_shader_path)
{
	m_Log.log_message(INFO_MESSAGE("starting program creation..."));
	std::string Vertex_shader;
	std::string Frag_shader;
	m_Log.log_message(INFO_MESSAGE("reading vertex shader..."));
	File_reader::file_reader()->file_to_string(Vertex_shader_path, Vertex_shader);
	if (Vertex_shader.empty())
	{
		m_Log.log_message(APP_ERROR_MESSAGE("Failed to read vertex shader..."));
		throw std::runtime_error("Failed to read vertex shader");
	}
	m_Log.log_message(INFO_MESSAGE("reading fragment shader..."));
	File_reader::file_reader()->file_to_string(Frag_shader_path, Frag_shader);
	if (Frag_shader.empty())
	{
		m_Log.log_message(APP_ERROR_MESSAGE("Failed to read fragment shader..."));
		throw std::runtime_error("Failed to read fragment shader...");
	}
	m_Log.log_message(INFO_MESSAGE("loading vertex shader..."));
	load_shader(Vertex_shader.c_str(), GL_VERTEX_SHADER);
	m_Log.log_message(INFO_MESSAGE("loading fragment shader..."));
	load_shader(Frag_shader.c_str(), GL_FRAGMENT_SHADER);
	m_Log.log_message(INFO_MESSAGE("completing program creation..."));
	create_program();
	m_Log.log_message(INFO_MESSAGE("program created."));
}

void Shader::create_program()
{
	GLint Success;
	GLchar Info_log[512];

	m_Log.log_message(INFO_MESSAGE("calling glCreateProgram()"));
	m_Program = glCreateProgram();
	m_Log.log_message(INFO_MESSAGE("attaching vertex shader..."));
	glAttachShader(m_Program, m_Vertex_shader_id);
	m_Log.log_message(INFO_MESSAGE("attaching fragment shader..."));
	glAttachShader(m_Program, m_Fragment_shader_id);
	m_Log.log_message(INFO_MESSAGE("calling glLinkProgram()"));
	glLinkProgram(m_Program);
	glGetProgramiv(m_Program, GL_LINK_STATUS, &Success);
	if (!Success)
	{
		m_Log.log_message(APP_ERROR_MESSAGE("glLinkProgram failed..."));
		glGetProgramInfoLog(m_Program, 512, NULL, Info_log);
		m_Log.log_message(APP_ERROR_MESSAGE(Info_log));
		throw std::runtime_error(Info_log);
	}
	m_Log.log_message(INFO_MESSAGE("glLinkProgram() succeeded..."));
	m_Log.log_message(INFO_MESSAGE("deleting vertex and fragment shaders..."));
	glDeleteShader(m_Vertex_shader_id);
	glDeleteShader(m_Fragment_shader_id);
}

void Shader::load_shader(const GLchar* Shader_str, GLenum Type)
{
	if (Type == GL_FRAGMENT_SHADER)
	{
		m_Log.log_message(INFO_MESSAGE("Loading fragment shader..."));
	}
	else
	{
		m_Log.log_message(INFO_MESSAGE("Loading vertex shader..."));
	}
	GLint Success;
	GLchar Info_log[512];
	m_Log.log_message(INFO_MESSAGE("Calling glCreateShader()"));
	GLuint Shader_id = glCreateShader(Type);
	m_Log.log_message(INFO_MESSAGE("Loading shader source"));
	glShaderSource(Shader_id, 1, &Shader_str, NULL);
	m_Log.log_message(INFO_MESSAGE("Calling glCompileShader()"));
	glCompileShader(Shader_id);
	glGetShaderiv(Shader_id, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(Shader_id, 512, NULL, Info_log);
		m_Log.log_message(APP_ERROR_MESSAGE("glCompileShader() failed..."));
		m_Log.log_message(APP_ERROR_MESSAGE(Info_log));
		throw std::runtime_error(Info_log);
	}
	m_Log.log_message(INFO_MESSAGE("glCompileShader() succeeded..."));
	(Type == GL_FRAGMENT_SHADER) ? m_Fragment_shader_id = Shader_id : m_Vertex_shader_id = Shader_id;

}

