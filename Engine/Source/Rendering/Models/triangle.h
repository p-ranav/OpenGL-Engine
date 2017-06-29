#pragma once

// User-defined Headers
#include "model.h"

namespace Rendering
{
	namespace Models
	{
		class Triangle : public Model
		{
		public:
			Triangle();
			~Triangle();

			void Create();
			virtual void Update() override final;
			virtual void Draw() override final;
		};
	}
}