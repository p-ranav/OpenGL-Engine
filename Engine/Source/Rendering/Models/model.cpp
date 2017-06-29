// User-defined Headers
#include "model.h"

// Call Destroy and cleanup vao and vbos of the model
Rendering::Models::Model::~Model()
{
	Destroy();
}

// Draw method will be overridden
void Rendering::Models::Model::Draw() {}

// Update method will be overridden
void Rendering::Models::Model::Update() {}

// Set the shader program of this model
void Rendering::Models::Model::SetProgram(GLuint program)
{
	this->program = program;
}

// Return model's vao
GLuint Rendering::Models::Model::GetVao() const
{
	return vao;
}

// Return const reference to model's vbos vector
const std::vector<GLuint>& Rendering::Models::Model::GetVbos() const
{
	return vbos;
}

// Delete vao and vbos
void Rendering::Models::Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(static_cast<GLsizei>(vbos.size()), &vbos[0]);
	vbos.clear();
}