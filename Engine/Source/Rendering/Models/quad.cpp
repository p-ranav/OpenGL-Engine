#include "quad.h"
using namespace Rendering;
using namespace Models;

Quad::Quad()
{}

Quad::~Quad()
{}

void Quad::Create()
{
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.5, 0.0),//pos
		glm::vec4(1, 0, 0, 1)));   //color
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.75, 0.0),//pos
		glm::vec4(0, 0, 0, 1)));   //color
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.5, 0.0),  //pos
		glm::vec4(0, 1, 0, 1)));   //color
								   //4th vertex
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.75, 0.0),//pos
		glm::vec4(0, 0, 1, 1)));   //color
								   //nothing different from Triangle model
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);            //here we have 4
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

}

void Quad::Update()
{
	//nothing here for the moment
}

void Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}