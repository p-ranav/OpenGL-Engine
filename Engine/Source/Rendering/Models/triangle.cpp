// User-defined Headers
#include "triangle.h"

/**
 * (1) Create the set of vertices
 * (2) Create and bind vbo and vao
 */
void Rendering::Models::Triangle::Create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertices + per-vertex Colors for this triangle
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0),
		glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0),
		glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0),
		glm::vec4(0, 0, 1, 1)));

	// Bind vbo and link vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	// Attribute Pointer for vertex position (vec3)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	// Attribute Pointer for vertex color (vec4)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);

	// Save vao and vbo in model
	this->vao = vao;
	this->vbos.push_back(vbo);
}

// Lame triangle is lame - No updates here
void Rendering::Models::Triangle::Update() {}

/**
 * Overrides Model's Draw method
 * (1) Use Shader Program
 * (2) Bind avo
 * (3) Draw vertices
 */
void Rendering::Models::Triangle::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}