#version 450 core
layout (location = 0) in vec3 in_position;

out vec3 texture_coordinates;

uniform mat4 projection;
uniform mat4 view;

void main() {
    texture_coordinates = in_position;
    gl_Position = projection * view * vec4(in_position, 1.0);
}  