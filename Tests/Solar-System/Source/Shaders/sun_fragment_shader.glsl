#version 330 core

uniform sampler2D sun_texture;

in vec2 texcoord;

layout (location=0) out vec4 out_color;

void main()
{
	vec4 color = texture(sun_texture, texcoord);
	out_color = color;
}