#pragma once

// User-defined Headers
#include "vertex_format.h"

// External Headers
#include "glew.h"
#include "freeglut.h"

// System Headers
#include <vector>
#include <iostream>

namespace Rendering
{
	/**
	 * Interface Class for Rendered Objects in our Engine
	 */
	class ObjectInterface
	{
	public:

		/**
		 * Abstract Base Class Destructor
		 */
		virtual ~ObjectInterface() = 0;

		/**
		 * Every renderable object has a Draw call
		 */
		virtual void Draw() = 0;

		/**
		 * Every renderable object has a Update call
		 */
		virtual void Update() = 0;

		/**
		 * Set a shader program for this object
		 */
		virtual void SetProgram(GLuint shader_name) = 0;

		/**
		 * Teardown this object
		 */
		virtual void Destroy() = 0;

		/**
		 * Get the vertex array object of this object
		 * @return Identifier for the vao of this object
		 */
		virtual GLuint GetVao() const = 0;

		/**
		 * Get the vertex buffer objects of this object
		 * @return vector of identifiers for the vbos of this object
		 */
		virtual const std::vector<GLuint>& GetVbos() const = 0;
	};

	// Inline Default Destructor Implementation
	inline ObjectInterface::~ObjectInterface() {}

}