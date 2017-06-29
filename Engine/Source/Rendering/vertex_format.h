#pragma once

// External Headers
#include "glm.hpp"

namespace Rendering
{

	/**
	 * VertexFormat structure
	 * Contains attributes of a vertex like:
	 * position, texture coordinates, normals, material etc.
	 */
	struct VertexFormat
	{
		/**
		 * Vertex Format Constructor
		 * @param vertex_position Position vector of vertex
		 * @param vertex_color Color of the vertex
		 */
		VertexFormat(const glm::vec3& vertex_position, const glm::vec4& vertex_color) {
			position = vertex_position;
			color = vertex_color;
		}

		/* Vertex Position in 3D space */
		glm::vec3 position;

		/* Vertex Color */
		glm::vec4 color;
	};

}