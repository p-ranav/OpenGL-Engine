/*
 * Author: Pranav Srinivas Kumar
 */

// User-defined Headers
#include "shader_loader.h"

// System Headers
#include<iostream>
#include<fstream>
#include<vector>

// Read Shader from file and return shader code
std::string Core::ShaderLoader::ReadShader(char *filename)
{
	// Return string
	std::string shader_code;

	// File Handle
	std::ifstream file(filename, std::ios::in);

	// Was the file open successful?
	if (!file.good()) {
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	// Read contents of file and return string
	file.seekg(0, std::ios::end);
	shader_code.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shader_code[0], shader_code.size());
	file.close();
	return shader_code;
}

// CreateShader with the provided input parameters
GLuint Core::ShaderLoader::CreateShader(GLenum shader_type, std::string source, char* shader_name)
{
	// Variable for error checking
	int compile_result = 0;

	// Use glCreateShader to create the shader
	GLuint shader = glCreateShader(shader_type);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = static_cast<int>(source.size());

	// Initialize shader source from input source code
	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);

	// Run compile shader and check results
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	// Check for Errors
	if (compile_result == GL_FALSE) {
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shader_name << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

GLuint Core::ShaderLoader::CreateProgram(char* vertex_shader_filename, char* fragment_shader_filename)
{
	// Read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertex_shader_filename);
	std::string fragment_shader_code = ReadShader(fragment_shader_filename);

	// Call CreateShader and create vertex and fragment shaders with the source code in the files
	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	// Variable for error checking
	int link_result = 0;

	// Create the program handle, attach the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	// Link created program and check results
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	// Check for link errors
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	return program;
}