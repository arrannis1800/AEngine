#version 330

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 vertex_tex_coord;

out vec2 texture_coord;

void main()
{
	texture_coord = vertex_tex_coord;
	gl_Position = vec4(vertex_position, 0.0, 1.0);
}