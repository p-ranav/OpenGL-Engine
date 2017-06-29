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
		/**
		 * Concrete model class that future models will inherit from and override
		 */
		class Model : public ObjectInterface
		{
		public:

			/**
			 * Model Default Constructor
			 */
			Model() {}

			/**
			* Model Default Destructor
			*/
			virtual ~Model();

			/**
			* Every model has a Draw method - This method will be overridden
			*/
			virtual void Draw() override;

			/**
			 * Every model has a Update method - This method will be overridden
			 */
			virtual void Update() override;

			/**
			 * Set the internal shader program of this model
			 * @param program Shader program 
			 */
			virtual void SetProgram(GLuint program) override;

			/**
			 * Every model has a Destroy method - Cleanup vao and vbos
			 */
			virtual void Destroy() override;

			/**
			 * Get the vertex array object of this object
			 * @return Identifier for the vao of this object
			 */
			virtual GLuint GetVao() const override;

			/**
			 * Get the vertex buffer objects of this object
			 * @return vector of identifiers for the vbos of this object
			 */
			virtual const std::vector<GLuint>& GetVbos() const override;

		protected:

			/* Vertex Array Object of this model */
			GLuint vao;

			/* Shader Program for this model */
			GLuint program;

			/* Vertex Buffer Objects of this model */
			std::vector<GLuint> vbos;
		};
	}
}