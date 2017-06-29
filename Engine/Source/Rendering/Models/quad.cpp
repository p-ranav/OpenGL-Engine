// User-defined Headers
#include "quad.h"

/**
* (1) Create the set of vertices
* (2) Create and bind vbo and vao
*/
void Rendering::Models::Quad::Create()
{
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertices + per-vertex Colors for this quad
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.5, 0.0),
		glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.75, 0.0),
		glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.5, 0.0),
		glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.75, 0.0),//pos
		glm::vec4(0, 0, 1, 1)));

	// Bind vbo and link vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
}

// Lame triangle is lame - No updates here
void Rendering::Models::Quad::Update() {}

/**
* Overrides Model's Draw method
* (1) Use Shader Program
* (2) Bind avo
* (3) Draw vertices
*/
void Rendering::Models::Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}