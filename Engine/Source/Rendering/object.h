#pragma once

// User-defined Headers
#include "vertex_format.h"
#include "..\Managers\camera_manager.h"

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
		* Every renderable object has a Draw call that takes a camera object as input
		* @param camera object which has the projection_matrix and the view matrix
		*/
		virtual void Draw(Managers::CameraManager * camera) = 0;

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
		 * Set texture of the object
		 * @param texture_name Name of the texture
		 * @param texture Identifier of the texture
		 */
		virtual void SetTexture(std::string texture_name, GLuint texture) = 0;

		/**
		* Returns texture of the object
		* @param texture_name Name of the texture
		* @return texture ID associated with provided texture name
		*/
		virtual const GLuint GetTexture(std::string texture_name) const = 0;

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