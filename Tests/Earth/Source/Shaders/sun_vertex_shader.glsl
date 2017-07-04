#version 330 core

layout(location=0) in vec3 in_position;
layout(location=8) in vec2 in_texcoord;

// Model, View, Projection matrix.
uniform mat4 MVP;

out vec2 texcoord;

void main()
{
    gl_Position = MVP * vec4(in_position, 1);
	texcoord = in_texcoord;
}