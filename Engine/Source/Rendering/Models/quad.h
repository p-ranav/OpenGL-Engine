#pragma once

// User-defined Headers
#include "model.h"

namespace Rendering
{
	namespace Models
	{

		/**
		* Quad Class
		*/
		class Quad : public Models::Model
		{
		public:

			/**
			 * Quad Default Constructor
			 */
			Quad() {}

			/**
			* Quad Default Destructor
			*/
			~Quad() {}

			/**
			* (1) Create the set of vertices
			* (2) Create and bind vbo and vao
			*/
			void Create();

			/**
			* Overrides Model's Update method
			*/
			virtual void Draw() override final;

			/**
			* Overrides Model's Draw method
			* (1) Use Shader Program
			* (2) Bind avo
			* (3) Draw vertices
			*/
			virtual void Update() override final;
		};
	}
}