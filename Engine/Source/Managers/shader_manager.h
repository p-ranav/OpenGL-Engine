#pragma once

// External Headers
#include "glew.h"
#include "freeglut.h"

// External Headers
#include "spdlog\spdlog.h"

// System Headers
#include <iostream>
#include<fstream>
#include<vector>
#include <map>

namespace Managers
{
	/**
	 * ShaderManager Class
	 */
	class ShaderManager
	{
	public:

		/**
		 * ShaderManager Default Constructor
		 */
		ShaderManager(void) {}

		/**
		* ShaderManager Default Destructor
		*/
		~ShaderManager(void);

		/**
		* This method creates and compiles a shader (vertex or fragment)
		* @param shader_name Name of the shader
		* @param vertex_shader_filename Name of the vertex shader file
		* @param fragment_shader_filename Name of the fragment shader file
		* @return Non-zero value by which the created shader program can be referenced
		*/
		void CreateProgram(const std::string& shader_name, const std::string& vertex_shader_filename, const std::string& fragment_shader_filename);

		/**
		 * Fetch shader from internal shader map
		 * @return Non-zero value by which the created shader program can be referenced
		 */
		static const GLuint GetShader(const std::string&);

	private:

		/**
		* Method to extract shader contents from file and
		* to create both shaders to load into program for
		* use in rendering loop.
		* @param filename Name of the shader file
		* @return shader code string
		*/
		std::string ReadShader(const std::string& filename);

		/**
		* Creates a shader with the provided parameters
		* @param shader_type Type of the shader to create
		* @param source source code of the shader
		* @param shader_name Name of the shader
		* @return Non-zero value by which the created shader program can be referenced
		*/
		GLuint CreateShader(GLenum shader_type, const std::string& source, const std::string& shader_name);

		/* Internal map of shader programs */
		static std::map<std::string, GLuint> programs;
	};

}