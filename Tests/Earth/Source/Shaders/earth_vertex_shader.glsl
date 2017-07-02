#version 450 core
layout(location=0) in vec3 in_position;
layout(location=2) in vec3 in_normal;
layout(location=8) in vec2 in_texcoord;

// Position in world space
out vec4 v2f_position_w;
// Surface normal in world space
out vec4 v2f_normal_w; 
out vec2 v2f_texture_coordinates;

// Model, View, Projection matrix.
uniform mat4 model_view_projection_matrix;
uniform mat4 model_matrix;

void main() {
    gl_Position = model_view_projection_matrix * vec4(in_position, 1);
    v2f_position_w = model_matrix * vec4(in_position, 1); 
    v2f_normal_w = model_matrix * vec4(in_normal, 0);
    v2f_texture_coordinates = in_texcoord;
}