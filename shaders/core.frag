#version 330 core
out vec4 Frag_color;

uniform vec4 Input_color;

void main()
{
	Frag_color = Input_color;
}