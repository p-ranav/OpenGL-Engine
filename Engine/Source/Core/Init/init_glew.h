#pragma once

// External Headers
#include "glew.h"
#include "freeglut.h"
#include "spdlog\spdlog.h"

// System Headers
#include <iostream>

namespace Core {

	namespace Init {
		
		/* Class to Initialize GLEW */
		class InitGLEW
		{
		public:
			/** 
			 * Initialize GLEW and check if GLEW GL_VERSION 4.5 is supported 
			 */
			static void Init();
		};
	}
}