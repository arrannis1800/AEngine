#version 330

in vec2 texture_coord;

out vec4 frag_color;

uniform sampler2D tex;

void main()
{
	frag_color = texture(tex, texture_coord);
}