#pragma once

// External Headers
#include "glew.h"
#include "freeglut.h"
#include "spdlog\spdlog.h"
#include "SOIL2.h"

// System Headers
#include <fstream>

namespace Rendering
{
	namespace Utilities
	{
		// Load BMP texture from file - Well this was easy.. Thanks SOIL!
		unsigned int LoadBMPTexture(const std::string& filename) {
			return SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		}
	}
}
