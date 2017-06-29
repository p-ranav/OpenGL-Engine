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
	class ObjectInterface
	{
	public:
		virtual ~ObjectInterface() = 0;

		virtual void Draw() = 0;
		virtual void Update() = 0;
		virtual void SetProgram(GLuint shaderName) = 0;
		virtual void Destroy() = 0;

		virtual GLuint GetVao() const = 0;
		virtual const std::vector<GLuint>& GetVbos() const = 0;
	};

	inline ObjectInterface::~ObjectInterface() {}

}