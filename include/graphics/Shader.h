#ifndef __SHADER_H_INCLUDED__
#define __SHADER_H_INCLUDED__

#include"Graphics_sys.h" // for opengl headers
#include"Log_file.h"
#include"File_reader.h"

class Shader
{
public:
	Shader();
	void create_program(const GLchar* Vertex_shader_path, const GLchar* Frag_shader_path);
	inline GLuint get_program() const
	{
		return Program;
	}
private:
	GLuint Program;
	GLuint Vertex_shader_id;
	GLuint Fragment_shader_id;
	void load_shader(const GLchar* Shader_str, GLenum Type);
	void create_program();
	Log_file Log;


};

#endif