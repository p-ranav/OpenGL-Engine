#pragma once

// User-defined Headers
#include "Rendering\Models\model.h"
#include "Managers\camera_manager.h"

// System Headers
#include <time.h>
#include <stdarg.h>

// Bitmap Texture Loading Functions
unsigned int Load2DBMPTexture(const std::string& filename, unsigned int width, unsigned int height);
void LoadBMPFromFile(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data);

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
			virtual void Draw(Managers::CameraManager* camera) override final;

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