#pragma once

// User-defined Headers
#include "model.h"

namespace Rendering
{
	namespace Models
	{
		/**
		 * Triangle Class - our most basic model
		 */
		class Triangle : public Model
		{
		public:

			/**
			 * Triangle Default Constructor
			 */
			Triangle() {}

			/**
			* Triangle Default Destructor
			*/
			~Triangle() {}

			/**
			 * (1) Create the set of vertices
			 * (2) Create and bind vbo and vao
			 */
			void Create();

			/**
			 * Overrides Model's Update method
			 */
			virtual void Update() override final;

			/**
			 * Overrides Model's Draw method
			 * (1) Use Shader Program
			 * (2) Bind avo
			 * (3) Draw vertices
			 */
			virtual void Draw() override final;
		};
	}
}