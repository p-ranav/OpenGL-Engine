/*
 * Author: Pranav Srinivas Kumar
 */
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

// External Headers
#include "glew.h"
#include "freeglut.h"

// System Headers
#include <iostream>

namespace Core
{
	/**
	 * ShaderLoader Class
	 * Used to create vertex and fragment shaders from file
	 */
	class ShaderLoader
	{
	public:

		/**
		 * ShaderLoader Default Constructor
		 */
		ShaderLoader() {}

		/**
		 * ShaderLoader Default Destructor
		 */
		~ShaderLoader() {}

		/**
		 * This method creates and compiles a shader (vertex or fragment)
		 * @param vertex_shader_filename Name of the vertex shader file
		 * @param fragment_shader_filename Name of the fragment shader file
		 * @return Non-zero value by which the created shader program can be referenced
		 */
		GLuint CreateProgram(char* vertex_shader_filename, char* fragment_shader_filename);

	private:

		/**
		 * Method to extract shader contents from file and 
		 * to create both shaders to load into program for 
		 * use in rendering loop.
		 * @param filename Name of the shader file
		 * @return shader code string
		 */
		std::string ReadShader(char *filename);

		/**
		 * Creates a shader with the provided parameters
		 * @param shader_type Type of the shader to create
		 * @param source source code of the shader
		 * @param shader_name Name of the shader
		 * @return Non-zero value by which the created shader program can be referenced
		 */
		GLuint CreateShader(GLenum shader_type, std::string source, char* shader_name);

	};

}

#endif