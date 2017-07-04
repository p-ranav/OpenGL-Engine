#version 450 core

layout(location = 0) out vec4 out_color;
uniform sampler2D sun;
in vec2 texcoord;

void main()
{
	vec4 color = texture(sun, texcoord);
    out_color = color;
}