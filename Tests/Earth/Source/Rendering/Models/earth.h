#pragma once

// User-defined Headers
#include "Rendering\Models\model.h"

// System Headers
#include <time.h>
#include <stdarg.h>
#include <cmath>

namespace Rendering
{
	namespace Models
	{
		/**
		* Earth Class
		*/
		class Earth : public Model
		{
		public:

			/**
			* (1) Create the set of vertices
			* (2) Create and bind vbo and vao
			*/
			void Create(float radius, float slices, float stacks);

			/**
			* Overrides Model's Draw method
			* (1) Use Shader Program
			* (2) Bind avo
			* (3) Draw vertices
			*/
			virtual void Draw(Managers::CameraManager* camera) override final;

			/**
			* Update rotation of the cube
			*/
			virtual void Update() override final;

		private:
			/* List of vertices in the icosphere */
			std::vector<VertexFormat> vertices;

			/* List of indices in the icosphere */
			std::vector<unsigned int> indices;

			std::vector<glm::vec3> positions_;
			std::vector<glm::vec3> normals_;
			std::vector<glm::vec2> texture_coordinates_;
		};
	}
}