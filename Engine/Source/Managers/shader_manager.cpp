/*
 * Author: Pranav Srinivas Kumar
 */

// User-defined Headers
#include "shader_manager.h"

// Definition of static member variable
std::map<std::string, GLuint> Managers::ShaderManager::programs;

/**
 * ShaderManager Destructor
 * Delete shader programs from internal map
 */
Managers::ShaderManager::~ShaderManager(void)
{
	std::map<std::string, GLuint>::iterator i;
	for (i = programs.begin(); i != programs.end(); ++i)
	{
		GLuint pr = i->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}

// Read Shader from file and return shader code
std::string Managers::ShaderManager::ReadShader(const std::string& filename)
{
	// Return string
	std::string shader_code;

	// File Handle
	std::ifstream file(filename, std::ios::in);

	// Was the file open successful?
	if (!file.good()) {
		std::cout << "Can't read file " << filename.c_str() << std::endl;
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
GLuint Managers::ShaderManager::CreateShader(GLenum shader_type, const std::string& source, const std::string& shader_name)
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
		std::cout << "ERROR compiling shader: " << shader_name.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

void Managers::ShaderManager::CreateProgram(const std::string& shader_name, const std::string& vertex_shader_filename, const std::string& fragment_shader_filename)
{
	// Check if shader with this name already exists in the internal map
	if (programs.find(shader_name) == programs.end()) {
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
		}

		programs[shader_name] = program;
	}
	else {
		std::cout << "Error: Shader with name " << shader_name.c_str() << " already exists. CreateProgram failed!" << std::endl;
		return;
	}
}

// Get Shader from internal map using shader_name
const GLuint Managers::ShaderManager::GetShader(const std::string& shader_name)
{
	// Check if shader_name exists in internal map
	if (programs.find(shader_name) != programs.end()) {
		return programs.at(shader_name);
	}
	else {
		std::cout << "Error: Shader with name " << shader_name.c_str() << " does not exist. GetShader failed!" << std::endl;
		return 0;
	}
}