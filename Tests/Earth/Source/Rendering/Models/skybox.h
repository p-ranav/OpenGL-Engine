#pragma once

// User-defined Headers
#include "Rendering\Models\model.h"

namespace Rendering
{
	namespace Models
	{
		/**
		* Skybox Class
		*/
		class Skybox : public Model
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
		};
	}
}