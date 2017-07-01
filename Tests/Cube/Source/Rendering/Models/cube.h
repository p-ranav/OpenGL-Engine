#pragma once

// User-defined Headers
#include "Rendering\Models\model.h"

// System Headers
#include <time.h>
#include <stdarg.h>

namespace Rendering
{
	namespace Models
	{
		/**
		 * Cube Class
		 */
		class Cube : public Model
		{
		public:

			/**
			* (1) Create the set of vertices
			* (2) Create and bind vbo and vao
			*/
			void Create();

			/**
			* Overrides Model's Draw method
			* (1) Use Shader Program
			* (2) Bind avo
			* (3) Draw vertices
			*/
			virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override final;

			/**
			 * Update rotation of the cube
			 */
			virtual void Update() override final;

		private:

			/* Rotation vector and rotation speed */
			glm::vec3 rotation, rotation_speed;
			glm::vec3 rotation_sin;
		};
	}
}