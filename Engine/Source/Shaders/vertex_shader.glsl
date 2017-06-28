#version 450 core                           //lower your version if GLSL 4.5 is not supported by your GPU
layout(location = 0) in vec3 in_position;  //set the first input on location (index) 0 ; in_position is our attribute 
 
void main()
{
  gl_Position = vec4(in_position, 1.0);//w is 1.0, also notice cast to a vec4
}