#pragma once

// User-defined Headers
#include "Rendering\Models\model.h"
#include "Managers\shader_manager.h"

// System Headers
#include <ctime>
#include <stdarg.h>
#include <cmath>

namespace Rendering
{
	namespace Models
	{
		/**
		* Solar System
		*/
		class SolarSystem : public Model
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
			* Update the Earth
			*/
			virtual void Update() override final;

		private:

			/**
			 * Internal Helper to Draw a Planet
			 */
			void DrawPlanet(GLuint shader_program, std::string planet_texture, 
				Managers::CameraManager* camera, int days_in_year, float distance_from_sun, 
				float planet_size, float planet_rotation);

			/* List of vertices in the icosphere */
			std::vector<VertexFormat> vertices;

			/* List of indices in the icosphere */
			std::vector<unsigned int> indices;

			/* Vertex positions */
			std::vector<glm::vec3> positions_;

			/* Vertex normals */
			std::vector<glm::vec3> normals_;

			/* Texture coordinates */
			std::vector<glm::vec2> texture_coordinates_;

			/* Clock ticks for rotation */
			std::clock_t current_ticks_, previous_ticks_;

			/* Rotation Parameters */
			float sun_rotation_;

			/* Planet Parameters - Day Counter + Rotation and Current Position */
			float mercury_rotation_, venus_rotation_, mars_rotation_, jupiter_rotation_,
				saturn_rotation_, uranus_rotation_, neptune_rotation_;

			/* Earth Parameters - Day Counter + Rotation and Current Position */
			float earth_rotation_, earth_day_count_, earth_position_x_, earth_position_y_;

			/* Moon Parameters - Day Counter + Rotation and Current Position */
			float moon_rotation_, moon_day_count_, moon_position_x_, moon_position_y_;
		};
	}
}