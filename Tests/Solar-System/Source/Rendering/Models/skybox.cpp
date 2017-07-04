// User-defined Headers
#include "skybox.h"

// Define PI for local use
#define PI 3.14159265

// Setup skybox (cube) vertices, colors, vao and vbo
void Rendering::Models::Skybox::Create() {
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices = {
		// Front Face
		0, 1, 2, 0, 2, 3,
		// Right Face
		4, 5, 6, 4, 6, 7,
		// Back Face
		8, 9, 10, 8, 10, 11,
		// Left Face
		12, 13, 14, 12, 14, 15,
		// Top Face
		16, 17, 18, 16, 18, 19,
		// Bottom Face
		20, 21, 22, 20, 22, 23 };

	// Front Face Vertices
	vertices.push_back(glm::vec3(-1500.0, -1500.0, 1500.0));
	vertices.push_back(glm::vec3(1500.0, -1500.0, 1500.0));
	vertices.push_back(glm::vec3(1500.0, 1500.0, 1500.0));
	vertices.push_back(glm::vec3(-1500.0, 1500.0, 1500.0));

	// Right Face Vertices 
	vertices.push_back(glm::vec3(1500.0, 1500.0, 1500.0));
	vertices.push_back(glm::vec3(1500.0, 1500.0, -1500.0));
	vertices.push_back(glm::vec3(1500.0, -1500.0, -1500.0));
	vertices.push_back(glm::vec3(1500.0, -1500.0, 1500.0));

	// Back Face Vertices 
	vertices.push_back(glm::vec3(-1500.0, -1500.0, -1500.0));
	vertices.push_back(glm::vec3(1500.0, -1500.0, -1500.0));
	vertices.push_back(glm::vec3(1500.0, 1500.0, -1500.0));
	vertices.push_back(glm::vec3(-1500.0, 1500.0, -1500.0));

	// Left Face Vertices 
	vertices.push_back(glm::vec3(-1500.0, -1500.0, -1500.0));
	vertices.push_back(glm::vec3(-1500.0, -1500.0, 1500.0));
	vertices.push_back(glm::vec3(-1500.0, 1500.0, 1500.0));
	vertices.push_back(glm::vec3(-1500.0, 1500.0, -1500.0));

	// Top Face Vertices 
	vertices.push_back(glm::vec3(1500.0, 1500.0, 1500.0));
	vertices.push_back(glm::vec3(-1500.0, 1500.0, 1500.0));
	vertices.push_back(glm::vec3(-1500.0, 1500.0, -1500.0));
	vertices.push_back(glm::vec3(1500.0, 1500.0, -1500.0));

	// Bottom Face Vertices 
	vertices.push_back(glm::vec3(-1500.0, -1500.0, -1500.0));
	vertices.push_back(glm::vec3(1500.0, -1500.0, -1500.0));
	vertices.push_back(glm::vec3(1500.0, -1500.0, 1500.0));
	vertices.push_back(glm::vec3(-1500.0, -1500.0, 1500.0));

	// Bind vbo
	glGenBuffers(1, &vbo);
	// Array Buffer Size for Vertices = Number of Vertices * size of each vertex 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// Bind ibo
	glGenBuffers(1, &ibo);
	// Array Buffer Size for Indices = Number of Indices * size of each index (unsigned int)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
}

// Nothing to update. Boring skybox is boring
void Rendering::Models::Skybox::Update() {}

// Draw skybox
void Rendering::Models::Skybox::Draw(Managers::CameraManager* camera) 
{
	// Map shader variables
	glUseProgram(program); 

	glBindVertexArray(vao);
	// Bind Texture
	glBindTexture(GL_TEXTURE_CUBE_MAP_SEAMLESS, this->GetTexture("skybox_texture"));

	glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, glm::value_ptr(camera->GetProjectionMatrix()));

	glDrawElements(GL_TRIANGLE_STRIP, 36, GL_UNSIGNED_INT, 0);
}
