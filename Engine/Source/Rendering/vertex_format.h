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
		/* Vertex Position in 3D space */
		glm::vec3 position;

		/* Vertex Color */
		glm::vec4 color;

		/* Texture Coordinates */
		glm::vec2 texture;

		/**
		 * Vertex Format Overloaded Constructor
		 * @param vertex_position Position vector of vertex
		 * @param vertex_color Color of the vertex
		 */
		VertexFormat(const glm::vec3& vertex_position, const glm::vec4& vertex_color) {
			position = vertex_position;
			color = vertex_color;
			texture.x = texture.y = 0;
		}

		/**
		* Vertex Format Overloaded Constructor
		* @param vertex_position Position vector of vertex
		* @param vertex_texture Texture of the vertex
		*/
		VertexFormat(const glm::vec3& vertex_position, const glm::vec2& vertex_texture) {
			position = vertex_position;
			texture = vertex_texture;
			color.r = color.g = color.b = color.a = 0;
		}
	};

}