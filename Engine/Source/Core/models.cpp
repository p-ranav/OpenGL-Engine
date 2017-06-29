/*
* Author: Pranav Srinivas Kumar
*/

// User-defined Headers
#include "models.h"

/**
 * GameModels Destructor
 * (1) Delete the vertex array objects
 * (2) Delete the vertex buffer objects in each model
 * (3) Clear the model map
 */
Models::GameModels::~GameModels()
{
	for (auto it = model_map_.begin(); it != model_map_.end(); ++it) {
		// Delete VAO and VBOs (if many)
		unsigned int* p = &it->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(static_cast<GLsizei>(it->second.vbos.size()), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	model_map_.clear();
}

/**
 * Creates a triangle model and stores in map
 */
void Models::GameModels::CreateTriangleModel(const std::string& model_name)
{
	unsigned int vao, vbo;

	// Bind vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex Positions and Colors of this silly little triangle
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0), glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0), glm::vec4(0, 0, 1, 1)));

	// Bind vbo and allocate space
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);

	// Add model to internal model map
	ModelStruct triangle_model;
	triangle_model.vao = vao;
	triangle_model.vbos.push_back(vbo);
	model_map_[model_name] = triangle_model;

}

/**
 * Find model from the model map and return the vao identifier of this model
 */
unsigned int Models::GameModels::GetModel(const std::string& model_name)
{
	return model_map_[model_name].vao;
}

/**
 * Delete a model from the internal model map
 * (1) Fetch the model from the map
 * (2) Delete the vao of the model
 * (3) Delete the vbos of the model
 * (4) Clear vbos vector in the model struct
 * (5) Erase model entry from internal model map
 */
void Models::GameModels::DeleteModel(const std::string& model_name)
{
	ModelStruct model = model_map_[model_name];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(static_cast<GLsizei>(model.vbos.size()), &model.vbos[0]);
	model.vbos.clear();
	model_map_.erase(model_name);

}