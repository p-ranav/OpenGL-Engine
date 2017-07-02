// User-defined Headers
#include "model.h"

// Call Destroy and cleanup vao and vbos of the model
Rendering::Models::Model::~Model() {
	Destroy();
}

// Draw methods will be overridden
void Rendering::Models::Model::Draw() {}
void Rendering::Models::Model::Draw(Managers::CameraManager* camera) {}

// Update method will be overridden
void Rendering::Models::Model::Update() {}

// Set the shader program of this model
void Rendering::Models::Model::SetProgram(GLuint program) {
	this->program = program;
}

// Return model's vao
GLuint Rendering::Models::Model::GetVao() const {
	return vao;
}

// Return const reference to model's vbos vector
const std::vector<GLuint>& Rendering::Models::Model::GetVbos() const {
	return vbos;
}

// Delete vao and vbos
void Rendering::Models::Model::Destroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(static_cast<GLsizei>(vbos.size()), &vbos[0]);
	vbos.clear();
}

// Set new texture for this model in the model's internal map
void Rendering::Models::Model::SetTexture(std::string texture_name, GLuint texture) {
	if (texture == 0) return;
	textures[texture_name] = texture;
}

// Return texture from internal map with given texture name
const GLuint Rendering::Models::Model::GetTexture(std::string texture_name) const {
	return textures.at(texture_name);
}