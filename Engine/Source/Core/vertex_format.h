/*
* Author: Pranav Srinivas Kumar
*/
#ifndef VERTEX_FORMAT_H
#define VERTEX_FORMAT_H

// External Headers
#include "glm.hpp"

/**
 * VertexFormat structure
 * Contains attributes of a vertex like:
 * position, texture coordinates, normals, material etc.
 */
struct VertexFormat
{
	/**
	 * Vertex Format Constructor
	 * @param position Position vector of vertex
	 */
	VertexFormat(const glm::vec3 &position) {
		vertex_position = position;
	}

	/* Vertex Position in 3D space */
	glm::vec3 vertex_position;
};

#endif