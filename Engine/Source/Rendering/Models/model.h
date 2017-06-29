#pragma once

// User-defined Headers
#include "../vertex_format.h"
#include "../object.h"

// External Headers
#include "glew.h"
#include "freeglut.h"

// System Headers
#include <vector>
#include <map>

namespace Rendering
{
	namespace Models
	{
		class Model : public ObjectInterface
		{
		public:
			Model() {}
			virtual ~Model();
			// methods from interface
			virtual void Draw() override;
			virtual void Update() override;
			virtual void SetProgram(GLuint shaderName) override;
			virtual void Destroy() override;

			virtual GLuint GetVao() const override;
			virtual const std::vector<GLuint>& GetVbos() const override;

		protected:
			GLuint vao;
			GLuint program;
			std::vector<GLuint> vbos;
		};
	}
}