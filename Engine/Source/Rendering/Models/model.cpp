// User-defined Headers
#include "model.h"

Rendering::Models::Model::~Model()
{
	Destroy();
}

void Rendering::Models::Model::Draw()
{
	//this will be again overridden
}

void Rendering::Models::Model::Update()
{
	//this will be again overridden
}

void Rendering::Models::Model::SetProgram(GLuint program)
{
	this->program = program;
}

GLuint Rendering::Models::Model::GetVao() const
{
	return vao;
}

const std::vector<GLuint>& Rendering::Models::Model::GetVbos() const
{
	return vbos;
}

void Rendering::Models::Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(static_cast<GLsizei>(vbos.size()), &vbos[0]);
	vbos.clear();
}