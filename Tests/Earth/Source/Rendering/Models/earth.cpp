// User-defined Headers
#include "earth.h"

// External Headers
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// System Headers
#include <vector>
#include <iostream>

// Define PI for local use
#define M_PI 3.1415926535897932384626433832795
#define M_2PI M_PI * 2

// Attribute Values
#define POSITION_ATTRIBUTE 0
#define NORMAL_ATTRIBUTE 2
#define DIFFUSE_ATTRIBUTE 3
#define SPECULAR_ATTRIBUTE 4
#define TEXCOORD0_ATTRIBUTE 8
#define TEXCOORD1_ATTRIBUTE 9
#define TEXCOORD2_ATTRIBUTE 10

#define BUFFER_OFFSET(offset) ((void*)(offset))
#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m)))

void Rendering::Models::Earth::Create(float radius, float slices, float stacks) {

	// Prepare vertices, normal and texture coordinates
	for (int i = 0; i <= stacks; ++i) {
		// V texture coordinate
		double V = i / static_cast<double>(stacks);
		double phi = V * M_PI;

		for (int j = 0; j <= slices; ++j) {
			// U texture coordinate
			double U = j / static_cast<double>(slices);
			double theta = U * M_2PI;

			double X = cos(theta) * sin(phi);
			double Y = cos(phi);
			double Z = sin(theta) * sin(phi);

			positions_.push_back(glm::vec3(X, Y, Z) * radius);
			normals_.push_back(glm::vec3(X, Y, Z));
			texture_coordinates_.push_back(glm::vec2(U, V));
		}
	}

	// Prepare indices for all these triangles
	for (int i = 0; i < slices * stacks + slices; ++i) {
		indices.push_back(i);
		indices.push_back(static_cast<GLuint>(i + slices + 1));
		indices.push_back(static_cast<GLuint>(i + slices));

		indices.push_back(static_cast<GLuint>(i + slices + 1));
		indices.push_back(static_cast<GLuint>(i));
		indices.push_back(static_cast<GLuint>(i + 1));
	}

	// Bind vao and vbos
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbos[4];
	glGenBuffers(4, vbos);

	// Vertex Position
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, positions_.size() * sizeof(glm::vec3), positions_.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(POSITION_ATTRIBUTE);

	// Vertex Normal
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3), normals_.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(NORMAL_ATTRIBUTE);

	// Texture Coordinate
	glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
	glBufferData(GL_ARRAY_BUFFER, texture_coordinates_.size() * sizeof(glm::vec2), texture_coordinates_.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(TEXCOORD0_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(TEXCOORD0_ATTRIBUTE);

	// Triangle Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->vbos.push_back(vbos[0]);
	this->vbos.push_back(vbos[1]);
	this->vbos.push_back(vbos[2]);
	this->vbos.push_back(vbos[3]);
	this->vao = vao;
}

void Rendering::Models::Earth::Update() {}

void Rendering::Models::Earth::Draw(Managers::CameraManager* camera) {
	const glm::vec4 white(1);
	const glm::vec4 black(0);
	const glm::vec4 ambient(0.1f, 0.1f, 0.1f, 1.0f);

	// Map shader variables
	glUseProgram(program);

	// Bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture("earth"));
	glUniform1i(glGetUniformLocation(program, "earth_texture"), 0);

	// Eye Position and Model Matrix
	glm::vec4 eyePosW = glm::vec4(camera->GetPosition(), 1);
	glm::mat4 modelMatrix = glm::rotate(glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(12.756f));

	// Properties of the Light Source
	glUniform4fv(glGetUniformLocation(program, "light_position_w"), 1, glm::value_ptr(modelMatrix[3])); // Need to add the light source (Sun)
	glUniform4fv(glGetUniformLocation(program, "light_color"), 1, glm::value_ptr(white));
	glUniform4fv(glGetUniformLocation(program, "ambient"), 1, glm::value_ptr(ambient));

	// Model View Projection Matrix
	modelMatrix = glm::rotate(glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(12.756f));
	glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(program, "model_view_projection_matrix"), 1, GL_FALSE, glm::value_ptr(mvp));
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform4fv(glGetUniformLocation(program, "eye_position_w"), 1, glm::value_ptr(eyePosW));

	// Material properties
	glUniform4fv(glGetUniformLocation(program, "material_emissive"), 1, glm::value_ptr(black));
	glUniform4fv(glGetUniformLocation(program, "material_diffuse"), 1, glm::value_ptr(white));
	glUniform4fv(glGetUniformLocation(program, "material_specular"), 1, glm::value_ptr(white));
	glUniform1f(glGetUniformLocation(program, "material_shininess"), 50.0f);
	
	glBindVertexArray(vao);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}