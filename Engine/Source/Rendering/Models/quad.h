#pragma once

// User-defined Headers
#include "model.h"

namespace Rendering
{
	namespace Models
	{
		class Quad : public Models::Model
		{
		public:
			Quad();
			~Quad();

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;
		};
	}
}